/* 
 * ****************************************************************************
 * debug_ns16550.c
 * ****************************************************************************
 */

/* 
 * ****************************************************************************
 * Include all header file
 * ****************************************************************************
 */
#include "..\..\include.h"

#ifdef __ENABLE_DBG_MSG__ /* { */
/* 
 * ****************************************************************************
 * Register define
 * ****************************************************************************
 */
#ifdef __UART_DEBUG_USE_UART1__
#define UART_PORT_BASE          REG_UART2_BASE
#else
#define UART_PORT_BASE          REG_UART1_BASE
#endif

/* 
 * ****************************************************************************
 * Structure define
 * ****************************************************************************
 */
struct NS16550
{
	unsigned char rbrthrdlb;	/* 0 */
	unsigned char ierdmb;		/* 1 */
	unsigned char iirfcrafr;	/* 2 */
	unsigned char lcr;		    /* 3 */
	unsigned char mcr;		    /* 4 */
	unsigned char lsr;		    /* 5 */
	unsigned char msr;		    /* 6 */
	unsigned char scr;		    /* 7 */
	unsigned char brsr;         /* 8 */
	unsigned char reserved[1];	/* 9 */
	unsigned char dsr;		    /* 10 */
	unsigned char dcr;		    /* 11 */
};

typedef volatile struct NS16550* NS16550_t;

#define rbr rbrthrdlb
#define thr rbrthrdlb
#define dll rbrthrdlb
#define ier ierdmb
#define dlm ierdmb
#define iir iirfcrafr
#define fcr iirfcrafr
#define afr iirfcrafr

#define IER_EMSI        0x08	/* Enable Modem Status Interrupt */
#define IER_ERLSI       0x04	/* Enable Recv Line Status Interrupt */
#define IER_ETHREI      0x02	/*
                                 * Enable Transmitter Holding Register Empty
                                 * Interrupt
                                 */
#define IER_ERDVI       0x01    /* Enable Recv Data Available Interrupt */

#define FCR_FIFO_EN     0x01	/*fifo enable */
#define FCR_RXSR        0x02	/*reciever soft reset */
#define FCR_TXSR        0x04	/*transmitter soft reset */
#define FCR_DMS		    0x08	/* DMA Mode Select */
#define FCR_FIFO_14     0xC0    /* 14 Byte FIFO Trigger*/
#define FCR_FIFO_8      0x80    /* 8 Byte FIFO Trigger*/
#define FCR_FIFO_4      0x40    /* 4 Byte FIFO Trigger*/
#define FCR_FIFO_1      0x00    /* 1 Byte FIFO Trigger*/

#define MCR_RTS         0x02	/* Readyu to Send */
#define MCR_LOOP	    0x10	/* Local loopback mode enable */
/* #define MCR_DTR         0x01    noton 8245 duart */
/* #define MCR_DMA_EN      0x04    noton 8245 duart */
/* #define MCR_TX_DFR      0x08    noton 8245 duart */

#define LCR_WLS_MSK 0x03	/* character length slect mask */
#define LCR_WLS_5   0x00	/* 5 bit character length */
#define LCR_WLS_6   0x01	/* 6 bit character length */
#define LCR_WLS_7   0x02	/* 7 bit character length */
#define LCR_WLS_8   0x03	/* 8 bit character length */
#define LCR_STB     0x04	/* Number of stop Bits, off = 1, on = 1.5 or 2) */
#define LCR_PEN     0x08	/* Parity eneble */
#define LCR_EPS     0x10	/* Even Parity Select */
#define LCR_STKP    0x20	/* Stick Parity */
#define LCR_SBRK    0x40	/* Set Break */
#define LCR_BKSE    0x80	/* Bank select enable - aka DLAB on 8245 */

#define LSR_DR      0x01	/* Data ready */
#define LSR_OE      0x02	/* Overrun */
#define LSR_PE      0x04	/* Parity error */
#define LSR_FE      0x08	/* Framing error */
#define LSR_BI      0x10	/* Break */
#define LSR_THRE    0x20	/* Xmit holding register empty */
#define LSR_TEMT    0x40	/* Xmitter empty */
#define LSR_ERR     0x80	/* Error */

#define MCR_LOOP    0x10
#define MCR_OUT2    0x08    /* enable interrupt */
#define MCR_OUT1    0x04
#define MCR_RTS     0x02
#define MCR_DTR     0x01

/* useful defaults for LCR*/
#define LCR_8N1     0x03

/* 
 * ****************************************************************************
 * Function
 * ****************************************************************************
 */
const NS16550_t COM_PORTS[] =
{
    (NS16550_t) (UART_PORT_BASE),
};

/**
 * ****************************************************************************
 * The function for init. uart interface
 *
 * @return
 *
 * @parameter
 * baudrate
 *
 * ****************************************************************************
 */
static volatile struct NS16550 *NS16550_init (int chan, int baudrate)
{
	volatile struct NS16550 *com_port;
    unsigned char param[2];

	com_port = (struct NS16550 *) UART_PORT_BASE ;

    if(baudrate <= 115200)
    {
        param[0] = 115200/baudrate;
        param[1] = 0;

        com_port->brsr = 0x00;
    }
    else
    {
       	param[0] = 460800/baudrate;
    	param[1] = 0x80;
        
        com_port->brsr = 0x02;  /* EC high speed select */
    }

	com_port->lcr = LCR_BKSE;	/* Access baud rate */
	com_port->dll = param[0];	/* 9600 baud */
	com_port->dlm = param[1];
	com_port->lcr = LCR_8N1;	/* 8 data, 1 stop, no parity */
	
    #ifdef __ENABLE_UART_INT_MODE__ /* { */
	    com_port->mcr = MCR_OUT2;	/* RTS/DTR */
	#else
	    com_port->mcr = 0;
	#endif /* } __ENABLE_UART_INT_MODE__ */

	/* Clear & enable FIFOs */
	com_port->fcr = FCR_FIFO_EN | FCR_RXSR | FCR_TXSR | FCR_FIFO_8;
	//com_port->brsr = 1; //by HW
	
    #ifdef __ENABLE_UART_INT_MODE__ /* { */
	com_port->ier = IER_ERDVI;  /* Enable Recv Data Available Interrupt */
	#else
	com_port->ier =  0;
	#endif /* } __ENABLE_UART_INT_MODE__ */

	return (com_port);
}

/**
 * ****************************************************************************
 * uart send character
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
static void NS16550_putc (volatile struct NS16550 *com_port, unsigned char c)
{
	volatile struct NS16550 *c_port = com_port;
    
	while ((c_port->lsr & LSR_THRE) == 0);
    
	c_port->thr = c;
}

/**
 * ****************************************************************************
 * uart debug put character
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void debug_putc(unsigned char c)
{
    NS16550_putc((struct NS16550*)UART_PORT_BASE, c);
}

/**
 * ****************************************************************************
 * The function for init./enable uart interface
 *
 * @return
 *
 * @parameter
 * baudrate
 *
 * ****************************************************************************
 */
void Uart_Init( void)
{
    #ifdef __UART_DEBUG_USE_UART1__
    /* UART2 ALT Funcntion Enable */
    /* GPCRH1 = ALT; */
    GPCRH2 = ALT;

    /*Uart 2 Enable, EC Side control */
    GCR1 |= 0x04;

    #ifdef __DISABLE_UART_AUTO_CLK_GATING__
    CLEAR_MASK(AUTOCG, BIT5);
    #endif /* #ifdef __DISABLE_UART_AUTO_CLK_GATING__ #endif */

    /* EC Side control */
    SET_MASK(RSTDMMC, BIT2);

    /* reset uart2 */
    RSTC4 = 0x04;
    #else
    /* UART1 ALT Funcntion Enable */
    GPCRE6 = ALT;
    
    /* Uart 1 Enable, EC Side control */
    GCR1 |= 0x01;

    #ifdef __DISABLE_UART_AUTO_CLK_GATING__
    CLEAR_MASK(AUTOCG, BIT6);
    #endif /* #ifdef __DISABLE_UART_AUTO_CLK_GATING__ #endif */

    /* EC Side control */
    SET_MASK(RSTDMMC, BIT3);
    
    /* reset uart1 */
    RSTC4 = 0x02;
    #endif

	NS16550_init(0, 115200);

    printf("[uart debug enabled]\n");
}

#endif /* } __ENABLE_DBG_MSG__ */
