/* 
 * ****************************************************************************
 * oem_scantabs.c
 * ****************************************************************************
 */

/* 
 * ****************************************************************************
 * Include all header file
 * ****************************************************************************
 */
#include "..\include.h"

//REJERRY089:Combine US and UK keyboard scan code table start.
//REJERRY008:S+ add Y510 scan code table.
const CBYTE Rc_ROM_Tables_Y510[] =   
{	// 15" US
	//00   01    02    03    04     05    06     07    08     09    10    11    12     13    14    15
	0x21,0x00,0xF9,0x8B,0x00,0x22,0x2A,0x3A,0x49,0x89,0x41,0x13,0x8D,0x4A,0x52,0x6A, // 00  //XITING0003:modify [0,0] from 0xF2 to 0x21.		//XITING0056:modify [0,2] from  0x15 to 0xF9.
	0xA7,0x00,0xA8,0x8A,0xF4,0x1A,0xF6,0x31,0xEE,0x88,0xA3,0x64,0x8C,0xED,0x5A,0xE7, // 01 //THOMASY014: change matrix[1,5] 0x32 to 0xF6
	0xAA,0x9E,0x8E,0x00,0x24,0xE1,0x34,0x33,0x5D,0x00,0xE6,0xAC,0x00,0x4E,0x5D,0xEC, // 02  
	0xA5,0x82,0x0D,0x00,0xE3,0xE0,0x2C,0x35,0x44,0x00,0xE5,0xE8,0x00,0xEB,0x00,0xF1, // 03  
	0xA6,0xAB,0x0E,0x00,0x58,0xF3,0x2E,0x36,0xE9,0x00,0xE4,0x51,0x00,0x45,0x55,0xF0, // 04  
	0xA9,0x00,0x16,0x00,0x26,0x1E,0xF5,0x3D,0x46,0x00,0x3E,0x61,0x00,0xF7,0x66,0xA0, // 05  //THOMASY014:change matrix[5,5] 0x25 to 0xF5; change matrix[5,13] 0x4D to 0xF7
	0xA4,0x00,0x67,0x00,0xE2,0x1D,0x2D,0x3C,0xEA,0x00,0x43,0xEF,0x00,0x54,0x5B,0xA1, // 06 
	0x00,0x77,0x1C,0x00,0x00,0x76,0x2B,0x3B,0x4B,0x9F,0xF2,0xF8,0x00,0x4C,0x23,0xA2, // 07 //REJERRY024:Modify matrix[7,9] from 0x00 to 0x9F.  //XITING0003:modify [7,10] from  0x21 to 0xF2.//XITING0057:modify [7,11] from  0x84 to 0xF8.
};

//------------------------------------------------------------------------------------
//        00    01    02    03    04    05    06    07    08    09    0A    0B    0C    0D    0E    0F
//------------------------------------------------------------------------------------
// 0-   48     x     17    62     x     47    49    52    54    57    53    133 64/56 55    41   14
// 1-  105    x     99    60    61    46    50    51    84     44   100   132   58    83    43   119
// 2-  106   101  59     x     19    113   35    36   29      x    118    96    x     12     42    89
// 3-   98    127  16     x    115   112   21    22   25      x    117   120    x    123    x    134
// 4-  103    91    1      x     30    32     6      7   121     x    116    56     x     11    13   125
// 5-  104    x      2      x      4     3      5      8    10      x      9  	45     x     26    15    92
// 6-   93     x    131    x    114   18    20    23   122    x      24    79     x     27    28    97
// 7-    x     90    31     x     86   110   34    37    39     x     38    129    x     40    33   102
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//       00    01    02    03    04    05    06    07    08    09    0A    0B    0C    0D    0E    0F
//------------------------------------------------------------------------------------
// 0-  C       x     Q    RAlt    x     X      V     M      .>   RShf  ,<    133RCtrl/56 /?  '"    JP14
// 1-  Kp-   x    Kp0  LAlt Space  Z      B     N    DnAr LShf  Kp*  132  LCtrl UpAr Enter  F8
// 2-  Kp+  Kp9  Fn     x      E     F2     G     H      \|     x     F7    Kp8   x     -_     #~    RiAr
// 3-  Kp2  LWin Tab   x      F4    F1     T     Y      O      x     F6    F9      x    F12     x    Vedio
// 4-  Kp3  Kp7  `~     x   CapsL  S     5%  6^   F10     x     F5   JP56    x     0)    =+    Del
// 5-  Kp.    x     1!     x     3#   2@    4$   7&    9(       x    8*   UK45   x     P     Back  Kp4
// 6-  Kp1   x    131    x     F3    W      R     U    F11     x      I     LeAr    x    [{      ]}    Kp5 
// 7-   x    NumL A      x     86    Esc    F      J      L      Kp/   K    App    x     ;:       D    Kp6
//------------------------------------------------------------------------------------

/*const CBYTE Rc_ROM_Tables_15UK_Y510[] =   
{	// 15" UK,JAP
	//00   01    02    03    04     05    06     07    08     09    10    11    12     13    14    15
	0xF2,0x00,0x15,0x8B,0x00,0x22,0x2A,0x3A,0x49,0x00,0x41,0x13,0x8D,0x4A,0x52,0x6A, // 00  
	0xA7,0x00,0xA8,0x8A,0xF4,0x1A,0x32,0x31,0xEE,0x88,0xA3,0x64,0x8C,0xED,0x5A,0xE7, // 01 
	0xAA,0x9E,0x8E,0x00,0x24,0xE1,0x34,0x33,0x5D,0x00,0xE6,0xAC,0x00,0x4E,0x00,0xEC, // 02
	0xA5,0x82,0x0D,0x00,0xE3,0xE0,0x2C,0x35,0x44,0x00,0xE5,0xE8,0x00,0xEB,0x00,0xF1, // 03  
	0xA6,0xAB,0x0E,0x00,0x58,0xF3,0x2E,0x36,0xE9,0x00,0xE4,0x51,0x00,0x45,0x55,0xF0, // 04  
	0xA9,0x00,0x16,0x00,0x26,0x1E,0x25,0x3D,0x46,0x00,0x3E,0x5D,0x00,0x4D,0x66,0xA0, // 05  //REJERRY023:add Kp/ to [5,9]. //REJERRY024:Modify matrix[5,9] from 0x9F to 0x00.
	0xA4,0x00,0x67,0x00,0xE2,0x1D,0x2D,0x3C,0xEA,0x89,0x43,0xEF,0x00,0x54,0x5B,0xA1, // 06
	0x00,0x77,0x1C,0x00,0x00,0x76,0x2B,0x3B,0x4B,0x9F,0x42,0x84,0x00,0x4C,0x23,0xA2, // 07 //REJERRY024:Modify matrix[7,9] from 0x00 to 0x9F.
};*/


const CBYTE Rc_ROM_Tables_15BR_Y510[] =
{	// 15" Brazil
	//00   01    02    03    04     05    06     07    08     09    10    11    12     13    14    15
	0x21,0x00,0xF9,0x8B,0x00,0x22,0x2A,0x3A,0x49,0x89,0x41,0x13,0x51,0x4A,0x52,0x6A, // 00 //REJERRY103:Modify BR keyboard matrix.[0,12] 51 to 8d //XITING0003:modify [0,0] from 0xF2 to 0x21.	//XITING0057:modify [0,12] from  0x8D to 0x51.		//XITING0056:modify [0,2] from  0x15 to 0xF9.
	0xA7,0x00,0xA8,0x8A,0xF4,0x1A,0xF6,0x31,0xEE,0x88,0xA3,0x64,0x8C,0xED,0x5A,0xE7, // 01  //THOMASY014: change matrix[1,5] 0x32 to 0xF6
	0xAA,0x9E,0x8E,0x00,0x24,0xE1,0x34,0x33,0x5D,0x00,0xE6,0xAC,0x00,0x4E,0x5D,0xEC, // 02
	0xA5,0x82,0x0D,0x00,0xE3,0xE0,0x2C,0x35,0x44,0x00,0xE5,0xE8,0x00,0xEB,0x00,0xF1, // 03   
	0xA6,0xAB,0x0E,0x00,0x58,0xF3,0x2E,0x36,0xE9,0x00,0xE4,0xF8,0x00,0x45,0x55,0xF0, // 04  			//XITING0057:modify [4,11] from  0x00 to 0xF8.
	0xA9,0x00,0x16,0x00,0x26,0x1E,0xF5,0x3D,0x46,0x00,0x3E,0x61,0x00,0xF7,0x66,0xA0, // 05  //THOMASY014:change matrix[5,5] 0x25 to 0xF5; change matrix[5,13] 0x4D to 0xF7
	0xA4,0x00,0x67,0x00,0xE2,0x1D,0x2D,0x3C,0xEA,0x00,0x43,0xEF,0x00,0x54,0x5B,0xA1, // 06
	0x00,0x77,0x1C,0x00,0x00,0x76,0x2B,0x3B,0x4B,0x9F,0xF2,0xF8,0x00,0x4C,0x23,0xA2, // 07 //REJERRY024:Modify matrix[7,9] from 0x00 to 0x9F.//1.REJERRY103:Modify BR keyboard matrix.[7,11]81 to84  //XITING0003:modify [7,10] from  0x21 to 0xF2.	//XITING0057:modify [7,11] from  0x51 to 0xF8.
};
//REJERRY008:E+ add Y510 scan code table.
//REJERRY089:Combine US and UK keyboard scan code table end.

//REJERRY004:Modify scan code table start.
const CBYTE Rc_ROM_Tables_IP710[] =   
{	// 15" US
	//00   01    02    03    04     05    06     07    08     09    10    11    12     13    14    15
	0x21,0x00,0xF9,0x8B,0x00,0x22,0x2A,0x3A,0x49,0x89,0x41,0x00,0x8D,0x4A,0x52,0x00, // 00  //REJERRY006:modify [0,0] from 0x21 to 0xF2.   //XITING0003:modify [0,0] from 0xF2 to 0x21.		//XITING0056:modify [0,2] from  0x15 to 0xF9.
	0xA7,0x00,0xA8,0x8A,0xF4,0x1A,0xF6,0x31,0xEE,0x88,0xA3,0x00,0x8C,0xED,0x5A,0xE7, // 01  //THOMASY014: change matrix[1,5] 0x32 to 0xF6
	0xAA,0x9E,0x8E,0x00,0x24,0xE1,0x34,0x33,0x5D,0x00,0xE6,0x9D,0x00,0x4E,0x00,0xEC, // 02
	0xA5,0x82,0x0D,0x00,0xE3,0xE0,0x2C,0x35,0x44,0x00,0xE5,0xE8,0x00,0xEB,0x00,0xF1, // 03  //THOMASY014: change matrix[1,15] 0x8E to 0xF1
	0xA6,0x9C,0x0E,0x00,0x58,0xF3,0x2E,0x36,0xE9,0x00,0xE4,0x00,0x00,0x45,0x55,0xF0, // 04  //REJERRY006:modify [4,5] from 0x1B to 0xF3.
	0xA9,0x00,0x16,0x00,0x26,0x1E,0xF5,0x3D,0x46,0x00,0x3E,0x00,0x00,0xF7,0x66,0xA0, // 05  //THOMASY014:change matrix[5,5] 0x25 to 0xF5; change matrix[5,13] 0x4D to 0xF7
	0xA4,0x00,0x00,0x00,0xE2,0x1D,0x2D,0x3C,0xEA,0x00,0x43,0xEF,0x00,0x54,0x5B,0xA1, // 06
	0x00,0x77,0x1C,0x00,0x00,0x76,0x2B,0x3B,0x4B,0x9F,0xF2,0x84,0x00,0x4C,0x23,0xA2, // 07  //REJERRY024:Modify matrix[7,9] from 0x00 to 0x9F.  //XITING0003:modify [7,10] from  0x21 to 0xF2.
};

//------------------------------------------------------------------------------------
//        00    01    02    03    04    05    06    07    08    09    0A    0B    0C    0D    0E    0F
//------------------------------------------------------------------------------------
// 0-   48     x     17    62     x     47    49    52    54    57    53    133 64/56 55    41   14
// 1-  105    x     99    60    61    46    50    51    84     44   100   132   58    83    43   119
// 2-  106   101  59     x     19    113   35    36 29/42  x     118    96    x     12     x     89
// 3-   98    127  16     x    115   112   21    22   25      x    117   120    x    123    x    134
// 4-  103    91    1      x     30    32     6      7   121     x    116    56     x     11    13   125
// 5-  104    x      2      x      4     3      5      8    10      x      9  	45     x     26    15    92
// 6-   93     x    131    x    114   18    20    23   122    x      24    79     x     27    28    97
// 7-    x     90    31     x     86   110   34    37    39     x      38   129    x     40    33    102
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//       00    01    02    03    04    05    06    07    08    09    0A    0B    0C    0D    0E    0F
//------------------------------------------------------------------------------------
// 0-  C       x     Q    RAlt    x     X      V     M      .>   RShf  ,<    133 RCtrl/56 /?  '"    JP14
// 1-  Kp-   x    Kp0  LAlt Space  Z      B     N    DnAr LShf  Kp*  132  LCtrl UpAr Enter  F8
// 2-  Kp+  Kp9  Fn     x      E     F2     G     H   \|/#~  x     F7    Kp8   x     -_      x    RiAr
// 3-  Kp2  LWin Tab   x      F4    F1     T     Y      O      x     F6    F9      x    F12     x     Fn
// 4-  Kp3  Kp7  `~     x   CapsL  S     5%  6^   F10     x     F5   JP56    x     0)    =+    Del
// 5-  Kp.    x     1!     x     3#   2@    4$   7&    9(      x     8*   UK45   x     P     Back  Kp4
// 6-  Kp1   x    131    x     F3    W      R     U    F11     x      I     LeAr    x    [{      ]}    Kp5 
// 7-   x    NumL A      x     86    Esc    F      J      L       x      K    App    x     ;:       D    Kp6
//------------------------------------------------------------------------------------

const CBYTE Rc_ROM_Tables_15UK_IP710[] =   
{	// 15" UK,JAP
	//00   01    02    03    04     05    06     07    08     09    10    11    12     13    14    15
	0x21,0x00,0xF9,0x8B,0x00,0x22,0x2A,0x3A,0x49,0x00,0x41,0x13,0x8D,0x4A,0x52,0x6A, // 00  //REJERRY006:modify [0,0] from 0x21 to 0xF2.		//XITING0003:modify [0,0] from 0xF2 to 0x21.		//XITING0056:modify [0,2] from  0x15 to 0xF9.
	0xA7,0x00,0xA8,0x8A,0xF4,0x1A,0xF6,0x31,0xEE,0x88,0xA3,0x64,0x8C,0xED,0x5A,0xE7, // 01  //THOMASY014: change matrix[1,5] 0x32 to 0xF6
	0xAA,0x9E,0x8E,0x00,0x24,0xE1,0x34,0x33,0x5D,0x00,0xE6,0x9D,0x00,0x4E,0x00,0xEC, // 02
	0xA5,0x82,0x0D,0x00,0xE3,0xE0,0x2C,0x35,0x44,0x00,0xE5,0xE8,0x00,0xEB,0x00,0xF1, // 03  //THOMASY014: change matrix[1,15] 0x8E to 0xF1
	0xA6,0x9C,0x0E,0x00,0x58,0xF3,0x2E,0x36,0xE9,0x00,0xE4,0x51,0x00,0x45,0x55,0xF0, // 04  //REJERRY006:modify [4,5] from 0x1B to 0xF3.
	0xA9,0x00,0x16,0x00,0x26,0x1E,0xF5,0x3D,0x46,0x00,0x3E,0x5D,0x00,0xF7,0x66,0xA0, // 05  //THOMASY014:change matrix[5,5] 0x25 to 0xF5; change matrix[5,13] 0x4D to 0xF7
	0xA4,0x00,0x67,0x00,0xE2,0x1D,0x2D,0x3C,0xEA,0x89,0x43,0xEF,0x00,0x54,0x5B,0xA1, // 06
	0x00,0x77,0x1C,0x00,0x00,0x76,0x2B,0x3B,0x4B,0x9F,0xF2,0x84,0x00,0x4C,0x23,0xA2, // 07  //REJERRY024:Modify matrix[7,9] from 0x00 to 0x9F.  //XITING0003:modify [7,10] from  0x21 to 0xF2.
};


const CBYTE Rc_ROM_Tables_15BR_IP710[] =
{	// 15" Brazil
	//00   01    02    03    04     05    06     07    08     09    10    11    12     13    14    15
	0x21,0x00,0xF9,0x8B,0x00,0x22,0x2A,0x3A,0x49,0x00,0x41,0x00,0x51,0x4A,0x52,0x00, // 00  //REJERRY006:modify [0,0] from 0x21 to 0xF2.		//XITING0003:modify [0,0] from 0xF2 to 0x21.		//XITING0056:modify [0,2] from  0x15 to 0xF9.
	0xA7,0x00,0xA8,0x8A,0xF4,0x1A,0xF6,0x31,0xEE,0x88,0xA3,0x00,0x8C,0xED,0x5A,0xE7, // 01  //THOMASY014: change matrix[1,5] 0x32 to 0xF6
	0xAA,0x9E,0x8E,0x00,0x24,0xE1,0x34,0x33,0x5D,0x00,0xE6,0x9D,0x00,0x4E,0x00,0xEC, // 02
	0xA5,0x82,0x0D,0x00,0xE3,0xE0,0x2C,0x35,0x44,0x00,0xE5,0xE8,0x00,0xEB,0x00,0xF1, // 03  //THOMASY014: change matrix[1,15] 0x8E to 0xF1
	0xA6,0x9C,0x0E,0x00,0x58,0xF3,0x2E,0x36,0xE9,0x00,0xE4,0x00,0x00,0x45,0x55,0xF0, // 04  //REJERRY006:modify [4,5] from 0x1B to 0xF3.
	0xA9,0x00,0x16,0x00,0x26,0x1E,0xF5,0x3D,0x46,0x00,0x3E,0x5D,0x00,0xF7,0x66,0xA0, // 05  //THOMASY014:change matrix[5,5] 0x25 to 0xF5; change matrix[5,13] 0x4D to 0xF7
	0xA4,0x00,0x00,0x00,0xE2,0x1D,0x2D,0x3C,0xEA,0x89,0x43,0xEF,0x00,0x54,0x5B,0xA1, // 06
	0x00,0x77,0x1C,0x00,0x00,0x76,0x2B,0x3B,0x4B,0x9F,0xF2,0x84,0x00,0x4C,0x23,0xA2, // 07  //REJERRY024:Modify matrix[7,9] from 0x00 to 0x9F.  //XITING0003:modify [7,10] from  0x21 to 0xF2.
};
//REJERRY004:Modify scan code table end.

const CBYTE EtKey_ROM_Tables[] =
{
	/* 16   17   18		// 19X8 Scan Table */
	0x6C,0x90,0x00,
	0x6B,0x75,0x00,
	0x7D,0x7B,0x00,  
	0x74,0x79,0x00,
	0x69,0x73,0x00,
	0x70,0x72,0x00,
	0x7C,0x81,0x00,
	0x7A,0x71,0x00,
};

//JERRYCR007:e+ Add keyboard matrix.
//------------------
//    16   17   18
//------------------
//0-  91   95   x
//1-  92   96   x
//2- 101  105   x
//3- 102  106   x
//4-  93   97   x
//5-  99   98   x
//6- 100  108   x
//7- 103  104   x
//------------------
//------------------
//    16   17   18
//------------------
//0-  7    /    x
//1-  4    8    x
//2-  9    -    x
//3-  6    +    x
//4-  1    5    x
//5-  0    2    x
//6-  *   Gent  x
//7-  3    .    x
//------------------
const CBYTE KB_S3WakeUP_Tables[] =
{
/* Scanner Table 1 */
//00   01   02   03   04   05   06   07   08   09   10   11   12   13   14   15
0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,
0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,
0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,
0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,
0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,
0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,
0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,
0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55
};

const CBYTE EtKey_S3WakeUP_Tables[] =
{	
/* 16   17   18		// 19X8 Scan Table */
0x55,0x55,0x55,
0x55,0x55,0x55,
0x55,0x55,0x55,
0x55,0x55,0x55,
0x55,0x55,0x55,
0x55,0x55,0x55,
0x55,0x55,0x55,
0x55,0x55,0x55,
};

const CBYTE KB_NOKEY_Tables[] =
{
	0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55, //
 	0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55, //
   	0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55, //
 	0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55, //
  	0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55, //
  	0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55, //
  	0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55, //
  	0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55  //
};
//AIUU3_W19: modify for Save p80 to cmos funciton >>>>
#define Crisiskey01        0x8E   	// Fn
#define Crisiskey02        0x23  	// D  //BROOKEW043
#define Crisiskey03        0x2D     //R   //BROOKEW043

#define Crisiskey04        0x4D 	// P  //MARTINH067:add

#define Crisiskey05			0xE1	// F2    //REJERRY052: add
#define Crisiskey06			0xEB	// F12  //REJERRY052: add
#define DebugKeyO			0x44	// O	//THOMASY019: add

void CrisisHotkey01(BYTE event)
{
   if(event == MAKE_EVENT)
   {
      FnStatus = 1;
	  //RamDebug(0x99);
   }
   if(event == BREAK_EVENT)
   	{
      FnStatus = 0;
    }
}
void CrisisHotkey02(BYTE event)
{
   	if((event == MAKE_EVENT)&&(FnStatus==1))
   	{
       //SET_MASK(P80CMOSSts,P80CMOSDis); //MARTINH067:remove
		CombineKeyRN = 1;     //MARTINH067: Add
		//RamDebug(0x9A);   //MARTINH067:remove
	}
}
//MARTINH067:add start
void CrisisHotkey04(BYTE event)
{
   	if((event == MAKE_EVENT)&&(FnStatus==1)&&(1==CombineKeyRN))
   	{
		CombineKeyRN = 0;
		SET_MASK(P80CMOSSts,P80CMOSDis);
//MARTINH101: add start
       if(IS_MASK_CLEAR(BATTUPDATEFW, BIT0)&&(SysPowState = SYSTEM_S0))
       {
         ECQEvent(BIOS_DEBUG);
		 Debug_BRT_RC_C2_L = nRemainingCapL;
		 Debug_BRT_RC_C2_H = nRemainingCapH;
		 
		 Debug_BRT_PV_C6_L = nPresentVoltL;
		 Debug_BRT_PV_C6_H = nPresentVoltH;
		 Debug_BRT_FCC_CC_L	= nFullChgCapL;
		 Debug_BRT_FCC_CC_H	= nFullChgCapH;
		 Debug_BRT_AC_D2_L	= nAvgCurrentL;
		 Debug_BRT_AC_D2_H	= nAvgCurrentH;
       }	
//MARTINH101: add end
		RamDebug(0x9A);
	}
}
//MARTINH067:add end
//BROOKEW043:Modify Crisis function >>>>
void CrisisHotkey03(BYTE event)
{
   if(((event == MAKE_EVENT)||(event==REPEAT_EVENT))&&(FnStatus == 1))	
	{
		SET_MASK(SYS_MISC1,Crisis_On);
	}
	else 
   {
	  CLEAR_MASK(SYS_MISC1,Crisis_On);
	}
}
//BROOKEW043:Modify Crisis function <<<

//REJERRY052:S+ add CrisisHotkey05 function.
void CrisisHotkey05(BYTE event)
{
	if((IS_MASK_CLEAR(ACPI_HOTKEY, HotkeyDisable))&&(FnStatus == 1))//"Fn+F2"
	{
		//F2_Pressed = 0xF2;  //REJERRY067:remove.
		SET_MASK(F2_Pressed, F2Flag); //REJERRY067:add.
		CLEAR_MASK(F2_Pressed, F12Flag); //REJERRY067:add.
	}
	else if((IS_MASK_SET(ACPI_HOTKEY, HotkeyDisable))&&(FnStatus == 0))//"F2"
	{
		//F2_Pressed = 0xF2;  //REJERRY067:remove.
		SET_MASK(F2_Pressed, F2Flag); //REJERRY067:add.
		CLEAR_MASK(F2_Pressed, F12Flag); //REJERRY067:add.
	}
}
//REJERRY052:E+.

//REJERRY067:S+ add CrisisHotkey06 function.
void CrisisHotkey06(BYTE event)
{
	if((IS_MASK_CLEAR(ACPI_HOTKEY, HotkeyDisable))&&(FnStatus == 1))//"Fn+F12"
	{
		SET_MASK(F2_Pressed, F12Flag); //REJERRY067:add.
		CLEAR_MASK(F2_Pressed, F2Flag); //REJERRY067:add.
	}
	else if((IS_MASK_SET(ACPI_HOTKEY, HotkeyDisable))&&(FnStatus == 0))//"F12"
	{
		SET_MASK(F2_Pressed, F12Flag); //REJERRY067:add.
		CLEAR_MASK(F2_Pressed, F2Flag); //REJERRY067:add.
	}
}
//REJERRY067:E+.

//THOMASY019:S+ add Fn+D+P
void FnHotkeyPort80Log05(BYTE event)
{
	if((event == MAKE_EVENT)&&(FnStatus == 1)&&(CombineKeyRN==1))////JERRYB0040£ºchange "Fn+D"to"Fn+D+P".
	{
		SET_MASK(P80CMOSSts,P80CMOSDis);
		SET_MASK(ACPI_HOTKEY, b6Cmd_NoShut);//JERRYB0032:when battery mode press FN+D£¬do not cut power¡£
		//COMMON0002: add start
		P80Index_backup=P80Index;
		P80CMOS_backup[0]= P80CMOS[0];
		P80CMOS_backup[1]= P80CMOS[1];
		P80CMOS_backup[2]= P80CMOS[2];
		P80CMOS_backup[3]= P80CMOS[3];
		P80CMOS_backup[4]= P80CMOS[4];
		P80CMOS_backup[5]= P80CMOS[5];
		P80CMOS_backup[6]= P80CMOS[6];
		//COMMON0002: add end
	}
}
//THOMASY019:E+

const sBootHotKeyStruct asBootHotKeyStruct[]=
{
	{ Crisiskey01, CrisisHotkey01	},
	{ Crisiskey02, CrisisHotkey02	},
	{ Crisiskey03, CrisisHotkey03   },//BROOKEW043 Add 
	{ Crisiskey04, CrisisHotkey04   },//MARTINH067 Add 
	{ Crisiskey05, CrisisHotkey05   },//REJERRY052:add.
	{ Crisiskey06, CrisisHotkey06   },//REJERRY052:add.  //REJERRY067:change function.
	{ DebugKeyO,	FnHotkeyPort80Log05},
};
void CheckBootHotKey(BYTE matrix, BYTE event)
{
	BYTE index;
    for(index=0x00; index<(sizeof(asBootHotKeyStruct)/sizeof(sBootHotKeyStruct)); index++)
    {
		if(matrix==asBootHotKeyStruct[index].matrix)
	    {
	        (asBootHotKeyStruct[index].pfunction)(event);
            return;
        }
    }
   
}

//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
void OEM_Hook_Send_Key(BYTE table_entry, BYTE event)
{
//	if(SystemIsS0) //BROOKEW043 Remove >>>
//	{  
//		if (IS_MASK_CLEAR( SYS_MISC1,ACPI_OS))
//		{
			CheckBootHotKey(table_entry,event);
//		}
//	}  //BROOKEW043 Remove <<<<
}
//JERRYCR013 s+
//----------------------------------------------------------------------------
// The function of hotkey Fn + F1
//----------------------------------------------------------------------------
//REJERRY004:Modify hotkey function start.
void HotKey_Fn_F1(BYTE event) 
{
	//MUTE
	if(IS_MASK_SET(SYS_MISC1,ACPI_OS))//: REMOVE MBID_READY judge
	{
		if ( event == MAKE_EVENT )
		{
		    Buffer_Key(0xE0);	/* Buffer E0h prefix */
		    Buffer_Key(0x23);	/* Buffer base code */
		}
		else
		{
			if ( event == BREAK_EVENT )
			{
		    		Buffer_Key(0xE0);	/* Buffer E0h prefix */
		    		Buffer_Key(0xF0);	/* Buffer base code */
		    		Buffer_Key(0x23);	/* Buffer base code */
			}
		}
	}
	
}

//----------------------------------------------------------------------------
// The function of hotkey Fn + F2
//----------------------------------------------------------------------------
void HotKey_Fn_F2(BYTE event)
{
	//Volum down
 	if(IS_MASK_SET(SYS_MISC1,ACPI_OS))// : REMOVE MBID_READY judge
	{
		if ((event == MAKE_EVENT)||(event == REPEAT_EVENT))
		{
			Buffer_Key(0xE0);	/* Buffer E0h prefix */
			Buffer_Key(0x21);	/* Buffer base code */
		}
		else
		{
			if (event == BREAK_EVENT)
			{
				Buffer_Key(0xE0);	/* Buffer E0h prefix */
				Buffer_Key(0xF0);	/* Buffer E0h prefix */
				Buffer_Key(0x21);	/* Buffer base code */
			} 
		}
	 }
}

//----------------------------------------------------------------------------
// The function of hotkey Fn + F3
//----------------------------------------------------------------------------
void HotKey_Fn_F3(BYTE event)
{
	//Volum up
	if(IS_MASK_SET(SYS_MISC1,ACPI_OS))//// : REMOVE MBID_READY judge
	{
		if ((event == MAKE_EVENT)||(event == REPEAT_EVENT))
		{
			Buffer_Key(0xE0);	/* Buffer E0h prefix */
			Buffer_Key(0x32);	/* Buffer base code */
		}
		else
		{
			if (event == BREAK_EVENT)
			{
				Buffer_Key(0xE0);	/* Buffer E0h prefix */
				Buffer_Key(0xF0);	/* Buffer E0h prefix */
				Buffer_Key(0x32);	/* Buffer base code */	
			}
		}
	}
}

//----------------------------------------------------------------------------
// The function of hotkey Fn + F4
//----------------------------------------------------------------------------
void HotKey_Fn_F4(BYTE event)
{
	//Mic
	if(event == MAKE_EVENT)
	{
		if ( IS_MASK_SET(SYS_MISC1, ACPI_OS) )
		{
			uVPCeventSource = 0;
			uVPCeventSource2 = App_Control_Mic;
			ECSMI_SCIEvent(SDV_VPC_notify);     
		}
	}
}

void HotKey_Fn_F12(BYTE event)	//THOMASY014: change F5 to F12
{
	//Insert
	//if(IS_MASK_SET(SYS_MISC1,ACPI_OS))							//XITING0013: remove os key no check acpi_OS
	//{																//XITING0013: remove os key no check acpi_OS
		if ((event == MAKE_EVENT)||(event == REPEAT_EVENT))
		{
			Buffer_Key(0xE0);	//THOMASY014: change 0x03 to 0xE0
			Buffer_Key(0x70);	//THOMASY014: add
		}
		else
		{
			if((event == BREAK_EVENT))
			{
				Buffer_Key(0xE0);	//THOMASY014: add
				Buffer_Key(0xF0);
				Buffer_Key(0x70);	//THOMASY014: change 0x03 to 0x70
			}
		}
 	//}																//XITING0013: remove os key no check acpi_OS
}
/**
 * ****************************************************************************
 * The function of hotkey Fn + F11
 *
 * @return
 *
 * @parameter, MAKE_EVENT, BREAK_EVENT, or REPEAT_EVENT
 *
 * ****************************************************************************
 */
void HotKey_Fn_F11(BYTE event)	//THOMASY014: change F6 to F11
{	
	if ( (IS_MASK_SET(SYS_MISC1, ACPI_OS)) && (TouchPadCount == 0))
	{
		if(event == MAKE_EVENT)
		{
			if(IS_MASK_SET(pDevStatus1,b5TPDRIVER_STATUS)) 
			{
				if(IS_MASK_SET(pDevStatus1,b7DisableTP))//enable TP//JERRYCR070:+Modify TP control flag.
				{			    
					CLEAR_MASK(pDevStatus1,b1F6DisableTP);
					ECSMI_SCIEvent(0x3E); 
					SET_MASK(pDevStus, pENABLE_TP);//JERRYCR054: Modify TP LED don't meet spec.
					CLEAR_MASK(GameZoneState, TPdisable); // REJERRY076: add.
					RamDebug1(0x55);  					
				}
				else  //Disable TP
				{
					SET_MASK(pDevStatus1,b1F6DisableTP);
					ECSMI_SCIEvent(0x3F); 
					CLEAR_MASK(pDevStus, pENABLE_TP);	// Turn on TouchPad.//JERRYCR054: Modify TP LED don't meet spec.
					SET_MASK(GameZoneState, TPdisable);	//REJERRY076: add.
					RamDebug1(0x65);
				}
				//SET_MASK(pDevStatus1,b0F6ScanCodeSend);//W121:e//JERRYCR056: -Optimize TP enable/disable function.
			}
			else
			{
				if (IS_MASK_SET(pDevStus, pENABLE_TP))
				{
					ECSend2Port(2, 0xF5);
					//TPCLK_OUTPUT;
					//TPCLK_LOW();
					EC_TP_ON_LOW();						//Disable TP
					SET_MASK(pDevStatus1, b7DisableTP);//Disable TP
					TouchPadCount = 3;
					CLEAR_MASK(pDevStus, pENABLE_TP);
					SET_MASK(GameZoneState, TPdisable);	//REJERRY076: add.
					RamDebug1(0x35); //JERRYCR055: Add TP debug ramdebug1.
				}
				else
				{
					//TPCLK_OUTPUT;
					//TPCLK_HI();
					//TPCLK_ALT;
					EC_TP_ON_HI();		//enable TP
					CLEAR_MASK(pDevStatus1, b7DisableTP);
					ECSend2Port(2, 0xF4);
					TouchPadCount = 3;
					SET_MASK(pDevStus, pENABLE_TP);
					CLEAR_MASK(GameZoneState, TPdisable); // REJERRY076: add.
					RamDebug1(0x45); //JERRYCR055: Add TP debug ramdebug1.
				}
			}
		}
		
		if (nVPCDriverIn==1)	// Check VPC driver.
		{
			uVPCeventSource = TouchPad;
			uVPCeventSource2 = 0;
			ECSMI_SCIEvent(SDV_VPC_notify);
		}
		ECQEvent(WIN_TP_EVENT); //REJERRY076: add
	}
}

void HotKey_Fn_F8(BYTE event)	//THOMASY014: change F7 to F8
{
	//Airplane
	if(event == MAKE_EVENT)
	{
		if ( IS_MASK_SET(SYS_MISC1, ACPI_OS) )
		{
			uVPCeventSource = 0;
			uVPCeventSource2 = App_Control_RF;
			ECSMI_SCIEvent(SDV_VPC_notify);     
			//ECSMI_SCIEvent(F7_Airplan_notify); 
		}
	}
}

/**
 * ****************************************************************************
 * The function of hotkey Fn + F8
 *
 * @return
 *
 * @parameter, MAKE_EVENT, BREAK_EVENT, or REPEAT_EVENT
 *
 * ****************************************************************************
 */
void HotKey_Fn_F9(BYTE event)	//THOMASY014: change F8 to F9
{
	//XITING0003:S+ change function to setting 
	if(IS_MASK_SET(SYS_MISC1,ACPI_OS))
	{
		if ((event == MAKE_EVENT)||(event == REPEAT_EVENT))
		{
			Buffer_Key(0xE0); //"Win" key
			Buffer_Key(0x1F);
			Buffer_Key(0x43); //"I" key
		}
		else
		{
			if (event == BREAK_EVENT)
			{
				Buffer_Key(0xE0); //"Win" key
				Buffer_Key(0xF0);
				Buffer_Key(0x1F);
				Buffer_Key(0xF0);
				Buffer_Key(0x43);
			}
		}
	}
	//Camera
	/*
	if(event == MAKE_EVENT)
	{
		if ( IS_MASK_SET(SYS_MISC1, ACPI_OS) )
		{
			nCameraPwrCHG;
			uVPCeventSource = Camera;
			uVPCeventSource2 = 0;
			ECSMI_SCIEvent(SDV_VPC_notify);
			CPL_MASK(pDevStus, pCamera);   
		}
	}*/
	//XITING0003:E+
}

/**
 * ****************************************************************************
 * The function of hotkey Fn + F10
 *
 * @return
 *
 * @parameter, MAKE_EVENT, BREAK_EVENT, or REPEAT_EVENT
 *
 * ****************************************************************************
 */

//THOMASY014: S+
void HotKey_Fn_F10(BYTE event)
{
	//XITING0003:S+ change function to camera enable/disable
	if(event == MAKE_EVENT)
	{
		if ( IS_MASK_SET(SYS_MISC1, ACPI_OS) )
		{
			nCameraPwrCHG;
			uVPCeventSource = Camera;
			uVPCeventSource2 = 0;
			ECSMI_SCIEvent(SDV_VPC_notify);
			CPL_MASK(pDevStus, pCamera);   
		}
	}	
	//WinKey disable/enable
	/*
	if(IS_MASK_SET(SYS_MISC1,ACPI_OS))
	{
		if(event == MAKE_EVENT)
		{
			if ( IS_MASK_SET(GameZoneState, winkeydisable) )
			{
				CLEAR_MASK(GameZoneState, winkeydisable);
			}
			else
			{
				SET_MASK(GameZoneState, winkeydisable);
			}

			ECQEvent(WIN_TP_EVENT);
		}
	}*/
	//XITING0003:E+
}
//THOMASY014: E+

void HotKey_Fn_F7(BYTE event)	//THOMASY014: change F10 to F7
{
	//Display mode
	//REJERRY027:remove hotkey enable mode, set default is disable mode.
	//if(IS_MASK_SET(ACPI_HOTKEY, HotkeyDisable))
	{
	  	if(event == MAKE_EVENT)
		{
			if ( IS_MASK_SET(SYS_MISC1, ACPI_OS) )
			{
				if( IS_MASK_CLEAR(SysStatus, FnF3WinKeyDn) )
				{
					e0_prefix_code(0x1F,event); // Win Key.
					SET_MASK(SysStatus, FnF3WinKeyDn);
				}
				simple_code(0x4D,event);		// P Key.
			}
		}
	
		if (event == BREAK_EVENT)
		{
			if ( IS_MASK_SET(SYS_MISC1, ACPI_OS) )
			{
				simple_code(0x4D,event);	// P Key.
				SET_MASK(SysStatus, FnF3PKeyUp);
			}
		}
	}
	/*else
	{
		if(IS_MASK_SET(SYS_MISC1,ACPI_OS))
       	{
			if ((event == MAKE_EVENT)||(event == REPEAT_EVENT))
			{
				Buffer_Key(0xE0);
				Buffer_Key(0x1F);
				Buffer_Key(0x4D);
			}
			else
			{
				if (event == BREAK_EVENT)
				{
					Buffer_Key(0xF0);
					Buffer_Key(0x4D);
					Buffer_Key(0xE0);
					Buffer_Key(0xF0);
					Buffer_Key(0x1F);
				}
			}
		}
	}*/
	//REJERRY027:remove end.
}

void HotKey_Fn_F5(BYTE event)	//THOMASY014: change F11 to F5
{
	//Brightness down
	if( event != BREAK_EVENT )
	{
		if( cBrightDnDelayCnt == 0 )
		{
			cBrightDnDelayCnt = Timer_5;
			uVPCeventSource = VPCeventBrightness;
			uVPCeventSource2 = 0;
			// Support for Windows 7 brightness control.
			if( (SYS_STATUS & 0x07) != 0 )		// Check DOS mode.
			{ 
				if( (SYS_STATUS & 0x07) == 0x03 )	
				{
					if( nBrightValue != 0 )
					{
						nBrightValue--;
						cRecoveryBrightValue = nBrightValue;
					}
					if (nVPCDriverIn==1)	// Check VPC driver.
					{ 
						ECQEvent(SDV_VPC_notify);
						ECQEvent(LCD_BRIG_DEC_EVENT); 
					}
				}
				else
				{
					ECQEvent(LCD_BRIG_DEC_EVENT); 
				}
			}	// 0x11 inform bios.
			//Support for Windows 7 brightness control.
			else
			{
				if( nBrightValue != 0 )
				{
					nBrightValue--;
					cRecoveryBrightValue = nBrightValue;
				}
			}
		}
		else
		{ 
			cBrightDnDelayCnt--; 
		}
	}
	else if( event == BREAK_EVENT )
	{ 
		cBrightDnDelayCnt = 0; 
	}
	
}


void HotKey_Fn_F6(BYTE event)	//THOMASY014: change F12 to F6
{
	////Brightness up
	if( event != BREAK_EVENT )
	{
		if( cBrightUpDelayCnt == 0 )
		{
			cBrightUpDelayCnt = Timer_5;
			uVPCeventSource = VPCeventBrightness;
			uVPCeventSource2 = 0;
			//G80:+S Support for Windows 7 brightness control.
			if( (SYS_STATUS & 0x07) != 0 )		// Check DOS mode.
			{ 
				if( (SYS_STATUS & 0x07) == 0x03 )	
				{
					if( nBrightValue < (BRIGHT_MAX_STEP - 1) )
					{
						nBrightValue++;
						cRecoveryBrightValue = nBrightValue;
					}
					if (nVPCDriverIn==1)	// Check VPC driver.
					{ 
						ECQEvent(SDV_VPC_notify);
						ECQEvent(LCD_BRIG_INC_EVENT); 
					}
				}
				else
				{
					ECQEvent(LCD_BRIG_INC_EVENT); 
				}
			}	// 0x11 inform bios.
			//Support for Windows 7 brightness control.
			else
			{
				if( nBrightValue < (BRIGHT_MAX_STEP - 1) )
				{
					nBrightValue++;
					cRecoveryBrightValue = nBrightValue;
				}
			}
		}
		else	
		{ 
			cBrightUpDelayCnt--;	  //Modify the Windows 7 brightness control caused by mistake.
		}
	}
	else if( event == BREAK_EVENT )
	{
		cBrightUpDelayCnt = 0;
	}
}


//----------------------------------------------------------------------------
// The function of hotkey Fn + SPACE
//----------------------------------------------------------------------------
void HotKey_Fn_Space(BYTE event)
{	
	//REJERRY047:S+.
	//if(SystemIsS5 || SystemIsS3)			//XITING0015:add DC_S5 check
	if(SystemNotS0)							//XITING0015:add DC_S5 check
	{
		return;
	}
	//REJERRY047:E+.
	
	if (event == MAKE_EVENT)
	{
		LED_KB_PWM_Step++; 
		if(LED_KB_PWM_Step == 3)
		{
			LED_KB_PWM_Step=0;
		}

		//REJERRY047:S+.
		if(LED_KB_PWM_Step!=0)
		{
			SET_MASK(EMStatusBit, b0SetKBLEDON);
		}
		else
		{
			CLEAR_MASK(EMStatusBit, b0SetKBLEDON);
		}
		//REJERRY047:E+.
	
		//CLEAR_MASK(EMStatusBit, b2KBLEDChk);//JERRYCR073:-Add shutting off keyboard lights under OKO Ultra saving mode.
		//CLEAR_MASK(EMStatusBit, b0SetKBLEDON);//JERRYCR073:-Add shutting off keyboard lights under OKO Ultra saving mode.
		UpdateLEDBL_delay = 25;			// Delay 3 sec for Update LED Back Light.
		if (nVPCDriverIn==1)
		{
			uVPCeventSource = General;
			uVPCeventSource2 = 0;
			ECSMI_SCIEvent(SDV_VPC_notify);
		}
	}
}
//REJERRY004:Modify hotkey function end.
//----------------------------------------------------------------------------
// The function of hotkey Fn + ESC
//----------------------------------------------------------------------------
void HotKey_Fn_ESC(BYTE event)
{
	//MARTINH026:add start
	if(event == MAKE_EVENT)
	{
		ECQEvent(PAGE_LOOK_notify); 
	}
}
/**
 * ****************************************************************************
 * The function of hotkey Fn + up arrow
 *
 * @return
 *
 * @parameter, MAKE_EVENT, BREAK_EVENT, or REPEAT_EVENT
 *
 * ****************************************************************************
 */
void HotKey_Fn_UP(BYTE event)
{
	if( event != BREAK_EVENT )
	{
		if( cBrightUpDelayCnt == 0 )
		{
			cBrightUpDelayCnt =5; //change Timer_5 direct to 5
			uVPCeventSource = VPCeventBrightness;
			uVPCeventSource2 = 0;
			if( (SYS_STATUS & 0x07) != 0 )		// Check DOS mode.
			{ 
				ECQEvent(LCD_BRIG_INC_EVENT); 
			}
			else
			{
				if( nBrightValue < (BRIGHT_MAX_STEP - 1) )
				{
					nBrightValue++;
					cRecoveryBrightValue = nBrightValue;
				}
			}
		}
		else
		{ 
			cBrightUpDelayCnt--; 
		}
	}
	else if( event == BREAK_EVENT )
	{
		cBrightUpDelayCnt = 0;
	}
}

void HotKey_Fn_DOWN(BYTE event)
{
	if( event != BREAK_EVENT )
	{
		if( cBrightDnDelayCnt == 0 )
		{
			cBrightDnDelayCnt = 5; //change Timer_5 direct to 5
			uVPCeventSource = VPCeventBrightness;
			uVPCeventSource2 = 0;
			if( (SYS_STATUS & 0x07) != 0 )		// Check DOS mode.
			{ 
				ECQEvent(LCD_BRIG_DEC_EVENT); 
			}
			else
			{
				if( nBrightValue != 0 )
				{
					nBrightValue--;
					cRecoveryBrightValue = nBrightValue;
				}
			}
		}
		else
		{ 
			cBrightDnDelayCnt--; 
		}
	}
	else if( event == BREAK_EVENT )
	{ 
		cBrightDnDelayCnt = 0; 
	}
}

void HotKey_Fn_LEFT(BYTE event)
{
	if(IS_MASK_SET(SYS_MISC1,ACPI_OS))// 
	{
		if ((event == MAKE_EVENT)||(event == REPEAT_EVENT))
		{
			Buffer_Key(0xE0);	/* Buffer E0h prefix */
			Buffer_Key(0x21);	/* Buffer base code */
		}
		else
		{
			if (event == BREAK_EVENT)
			{
				Buffer_Key(0xE0);	/* Buffer E0h prefix */
				Buffer_Key(0xF0);	/* Buffer E0h prefix */
				Buffer_Key(0x21);	/* Buffer base code */
			} 
		}
	}
	
}

void HotKey_Fn_RIGHT(BYTE event)
{
	if(IS_MASK_SET(SYS_MISC1,ACPI_OS))//// 
	{
		if ((event == MAKE_EVENT)||(event == REPEAT_EVENT))
		{
			Buffer_Key(0xE0);	/* Buffer E0h prefix */
			Buffer_Key(0x32);	/* Buffer base code */
		}
		else
		{
			if (event == BREAK_EVENT)
			{
				Buffer_Key(0xE0);	/* Buffer E0h prefix */
				Buffer_Key(0xF0);	/* Buffer E0h prefix */
				Buffer_Key(0x32);	/* Buffer base code */	
			}
		} 
	}
}
//JERRYCR013:+e
//----------------------------------------------------------------------------
// The function of hotkey Fn + Ins (Scr Lk)
//---------------------------------------------------------------------------
void HotKey_Fn_Plus(BYTE event)///W051:EM zoom function
{
	if(event == MAKE_EVENT)
	{
		if ( IS_MASK_SET(SYS_MISC1, ACPI_OS) )
		{    
			SET_MASK(EM9_NEWFUN, b0_FnPlus);
			uVPCeventSource = General;
			uVPCeventSource2 = 0;
			ECQEvent(SDV_VPC_notify); //MartinH011:change 
		}
	}
}
//----------------------------------------------------------------------------
// The function of hotkey Fn + Del (NumLk)
//---------------------------------------------------------------------------
void HotKey_Fn_Minus(BYTE event)///W051:EM Zoom function
{
	if(event == MAKE_EVENT)
	{
		if ( IS_MASK_SET(SYS_MISC1, ACPI_OS) )
		{
			//if(IS_MASK_SET(EM9_NEWFUN, b7_LShiftPress)||IS_MASK_SET(EM9_NEWFUN, b7_LShiftPress))  //W060
			SET_MASK(EM9_NEWFUN, b1_FnMinus);
			uVPCeventSource = General;
			uVPCeventSource2 = 0;
			ECQEvent(SDV_VPC_notify); //MartinH011:change 
		}
	}
}

void HotKey_Fn_R(BYTE event)			//crisis event
{

}

//REJERRY004:S+ add video hotkey function.
//HEGANG005:s+Optimize video key method follow lenovo and Synchronous state of TP.
void FunctionKey_Video(BYTE event) //Video(Y510)
{
	if(IS_MASK_CLEAR(WinKEY_STATE, WinKEY_STATE_Check))			//XITING0007: add if win press vedio key no function
	{
		if(IS_MASK_SET(SYS_MISC1,ACPI_OS))
		{
			if(event == MAKE_EVENT)
			{
				Buffer_Key(0x50);// F22
			}
			else if(event == BREAK_EVENT)
			{
				if(Vedio_Record_Key_Delay==0)
				{
					SET_MASK(Vedio_Record_Key_Reg, BIT0);
				}
				Buffer_Key(0xF0);
				Buffer_Key(0x50); //F22
			}
		} 
	}
}
//HEGANG005:e+Optimize video key method follow lenovo and Synchronous state of TP.
//REJERRY037:S+ add Nerve Center hotkey function.
void FunctionKey_NerveCenter(BYTE event) //Nerve Center(Y510)
{
	//XITING0003:S- remove nerveCenter
	/*
	if(IS_MASK_SET(SYS_MISC1,ACPI_OS))
    {
		if ((event == MAKE_EVENT)||(event == REPEAT_EVENT))
		{
			Buffer_Key(0x12); //"Shift" key
			Buffer_Key(0x14); //"Ctrl" key
			Buffer_Key(0x57); //"F23" key
		}
		else
		{
			if (event == BREAK_EVENT)
			{
				Buffer_Key(0xF0);
				Buffer_Key(0x12);
				Buffer_Key(0xF0);
				Buffer_Key(0x14);
				Buffer_Key(0xF0);
				Buffer_Key(0x57);
			}
		}
	}*/
	//XITING0003:E-	
}
//REJERRY037:E+ add Nerve Center hotkey function.

//THOMASY014: S+
void FunctionKey_Setting(BYTE event)
{
	//XITING0003:S- remove setting
	/*
	if(IS_MASK_SET(SYS_MISC1,ACPI_OS))
	{
		if ((event == MAKE_EVENT)||(event == REPEAT_EVENT))
		{
			Buffer_Key(0xE0); //"Win" key
			Buffer_Key(0x1F);
			Buffer_Key(0x43); //"I" key
		}
		else
		{
			if (event == BREAK_EVENT)
			{
				Buffer_Key(0xE0); //"Win" key
				Buffer_Key(0xF0);
				Buffer_Key(0x1F);
				Buffer_Key(0xF0);
				Buffer_Key(0x43);
			}
		}
	}*/
	//XITING0003:E-
}

void HotKey_Fn_Bluetooth(BYTE event)
{
	//disable/enable Bluetooth
	/*THOMASY017:S-
	if(event == MAKE_EVENT)
	{
		if ( IS_MASK_SET(SYS_MISC1, ACPI_OS) )
		{
			uVPCeventSource = 0;
			uVPCeventSource2 = App_Control_RF;
			ECSMI_SCIEvent(SDV_VPC_notify);
		}
	}*///THOMASY017:E-
}

void HotKey_Fn_Sleep(BYTE event)
{
	if(IS_MASK_SET(SYS_MISC1,ACPI_OS))
	{
		if ((event == MAKE_EVENT)||(event == REPEAT_EVENT))
		{
			Buffer_Key(0xE0); //"Sleep"
			Buffer_Key(0x3F);
		}
		else
		{
			if (event == BREAK_EVENT)
			{
				Buffer_Key(0xE0); //"Sleep"
				Buffer_Key(0xF0);
				Buffer_Key(0x3F);
			}
		}
	}
}
//THOMASY014: S+

//XITING0056:S add
void HotKey_Fn_FanCooling(BYTE event)
{
	if(IS_MASK_SET(SYS_MISC1,ACPI_OS))
	{	
		/*
		if ((event == MAKE_EVENT)||(event == REPEAT_EVENT))
		{
			Buffer_Key(0xE0); //"Sleep"
			Buffer_Key(0x3F);
		}
		else
		{
			if (event == BREAK_EVENT)
			{
				Buffer_Key(0xE0); //"Sleep"
				Buffer_Key(0xF0);
				Buffer_Key(0x3F);
			}
		}
		*/
		if (event == MAKE_EVENT)
		{
			if(IS_MASK_SET(GameZoneState1, FanCooling))
			{
				CLEAR_MASK(GameZoneState1, FanCooling);
				CLEAR_MASK(Thro_Status2, b4FAN1_FullOn);
			}
			else
			{
				SET_MASK(GameZoneState1, FanCooling);
				SET_MASK(Thro_Status2, b4FAN1_FullOn);
			}
		}
	}
}
//XITING0056:E

const FUNCT_PTR_V_B HotKey_Fn_Fx[] =
{
    /* Fn + F1 */
	HotKey_Fn_F1,
    /* Fn + F2 */
	HotKey_Fn_F2,
    /* Fn + F3 */
	HotKey_Fn_F3,
    /* Fn + F4 */
	HotKey_Fn_F4,
    /* Fn + F5 */
	HotKey_Fn_F5,
    /* Fn + F6 */
	HotKey_Fn_F6,
    /* Fn + F7 */
	HotKey_Fn_F7,
    /* Fn + F8 */
	HotKey_Fn_F8,
    /* Fn + F9 */
	HotKey_Fn_F9,
    /* Fn + F10 */
	HotKey_Fn_F10,
    /* Fn + F11 */
	HotKey_Fn_F11,
    /* Fn + F12	*/
	HotKey_Fn_F12,
    /* Fn + ESC	*/
	HotKey_Fn_ESC,
    /* Fn + up arrow */
	HotKey_Fn_UP,
    /* Fn + down arrow */
	HotKey_Fn_DOWN,
    /* Fn + left arrow */
	HotKey_Fn_LEFT,
  	/* Fn + right arrow	*/
	HotKey_Fn_RIGHT,
	HotKey_Fn_Plus,		// Fn + Ins (Scr Lk)
	HotKey_Fn_Minus,	// Fn + Del (NumLk)
	/* Fn + Del */
	HotKey_Fn_R,		// Fn + R (NumLk)
	HotKey_Fn_F1,    	// Fn + F1
	HotKey_Fn_F2, 		// Fn + F2
	HotKey_Fn_F3, 		// Fn + F3
	HotKey_Fn_F4,      	// Fn + F4
	HotKey_Fn_F5,    	// Fn + F5
	HotKey_Fn_F6, 		// Fn + F6
	HotKey_Fn_F7, 		// Fn + F7
	HotKey_Fn_F8,       // Fn + F8
	HotKey_Fn_F9,    	// Fn + F9
	HotKey_Fn_F10, 		// Fn + F10
	HotKey_Fn_F11, 		// Fn + F11
	HotKey_Fn_F12,    	// Fn + F12
	HotKey_Fn_Space,    // Fn + Space
	FunctionKey_Video,  //Video //REJERRY004:add video hotkey function.
	FunctionKey_NerveCenter, //Nerve Center  //REJERRY037:add Nerve Center hotkey function.
	FunctionKey_Setting, 	//Setting		//THOMASY014:add
	HotKey_Fn_Bluetooth, 	//Bluetooth 	//THOMASY014:add
	HotKey_Fn_Sleep,		//Fn+4 = Sleep  //THOMASY014:add
	HotKey_Fn_FanCooling,		//Fn+Q = FanCooling  	//XITING0056:add
};

/*
 * ****************************************************************************
 * Play/Pause   [9Fh] <-> Numpad 7(IP710)           Nerve Center[C6] <-> Numpad7(Y510)
 * Stop           [9Eh] <-> Numpad 8(IP710)           Play/Pause[9F] <-> Numpad8(Y510)
 * Prev Track	   [9Dh] <-> Numpad 9 
 * Next Track   [9Ch] <-> Numpad / 
 * NA                       <-> Numpad 4
 * NA                       <-> Numpad 5 
 * NA                       <-> Numpad 6
 * NA                       <-> Numpad *
 * Insert          [C2h] <-> Numpad 1
 * PrtSc           [C3h] <-> Numpad 2
 * Break          [92h] <-> Numpad 3
 * Pause          [91h] <-> Numpad -
 * NA                       <-> Numpad 0
 * Delete         [C0h] <-> Numpad .
 * NA                       <-> Numpad +
 * ****************************************************************************
 */
//REJERRY004:Modify Numpad key function start.
const BYTE ss2_9C[] =	// NA <-> Numpad 7  //REJERRY006:modify from "Nerve Center" to "Play/Pause".
{
    0x00,   // Normal    //THOMASY014:Modify from 0x9F to 0xE6. //THOMASY017:modify from 0xE6 to 0x00. remove Never Center In Y530
    0x6C,   // Numlock  
};

const BYTE ss2_9D[] =	// Setup <-> Numpad 8  //REJERRY006:modify from "Play/Pause" to "Stop".
{
    0xE7,   // Normal  //THOMASY014:Modify from 0x9E to 0xE7.
    0x75,   // Numlock
};

const BYTE ss2_9E[] = 	// Buletooth <-> Numpad 9
{
    0xE8,   // Normal	//THOMASY014: change 0x9D to 0xE8
    0x7D,   // Numlock 
};

const BYTE ss2_9F[] = 	// NA <-> Numpad /
{
    0x00,   // Normal 	//THOMASY014: change 0x9C to 0x00
    0xBE,   // Numlock 
};

const BYTE ss2_A0[] = 	// Play/Pause <-> Numpad 4
{
    0x9F,   // Normal  //THOMASY014: change 0x10 to 0x9F
    0x6B,   // Numlock 
};

const BYTE ss2_A1[] = 	// Stop <-> Numpad 5  
{
    0x9E,   // Normal  //THOMASY014: change 0x20 to 0x9E
    0x73,   // Numlock 
};

const BYTE ss2_A2[] =	// Prev Track <-> Numpad 6 
{
    0x9D,   // Normal  //THOMASY014: change 0x30 to 0x9D
    0x74,   // Numlock 
};

const BYTE ss2_A3[] =	// Next Track <-> Numpad *
{
    0x9C,   // Normal  //THOMASY014: change 0x7C to 0x9C
    0x7C,   // Numlock 
};

const BYTE ss2_A4[] = 	// NA <-> Numpad 1
{
    0x00,   // Normal 	//THOMASY014: change 0xC2 to 0x00
    0x69,   // Numlock 
};

const BYTE ss2_A5[] = 	// NA <-> Numpad 2
{
    0x00,   // Normal 	//THOMASY014: change 0xC3 to 0x00
    0x72,   // Numlock 
};

const BYTE ss2_A6[] =	// NA <-> Numpad 3
{
    0x00,   // Normal 	//THOMASY014: change 0x92 to 0x00
    0x7A,   // Numlock 
};

const BYTE ss2_A7[] = 	// NA <-> Numpad -
{
    0x00,   // Normal   //THOMASY014: change 0x91 to 0x00
    0x7B,   // Numlock 
};

const BYTE ss2_A8[] =	// NA <-> Numpad 0  
{
    0x00,   // Normal  //THOMASY017:modify from 0x40 to 0x00
    0x70,   // Numlock 
};

const BYTE ss2_A9[] = 	// NA <-> Numpad .  
{
    0x00,   // Normal 	//THOMASY014: change 0xC0 to 0x00
    0x71,   // Numlock 
};

const BYTE ss2_AA[] = 	// NA <-> Numpad +   
{
    0x00,   // Normal  //THOMASY014: change 0x79 to 0x00
    0x79,   // Numlock 
};
//REJERRY004:Modify Numpad key function end.

//REJERRY008:modify Numpad key function for Y510 start.
const BYTE ss2_AB[] = 	// NA <-> Numpad 7
{
    0x00,   // Normal  //THOMASY017:modify from 0xE6 to 0x00. remove Never Center In Y530
    0x6C,   // Numlock 
};

const BYTE ss2_AC[] =  //Setting <-> Numpad8
{
    0xE7,   // Normal 	//THOMASY014: change 0x9F to 0xE7
    0x75,   // Numlock 
};
//REJERRY008:modify Numpad key function for Y510 end.

const BYTE ss2_AD[] = 	// F1
{
	0xD0,   // Fn 
    	0x05,   // Normal  
};

const BYTE ss2_AE[] = 	// F2 	 
{
   	 0xD1,   // Fn 
   	 0x06,   // Normal 
};

const BYTE ss2_AF[] = 	// F3  
{
 	0xD2,   // Fn 
    	0x04,   // Normal 
   
};
const BYTE ss2_B0[] =	// F4   
{
    0xD3,   // Fn 
    0x0C,   // Normal 
};
const BYTE ss2_B1[] = 	// F5  
{
	0x03,
   	0x03,
};
const BYTE ss2_B2[] = 	// F6  
{
    0xD5,   // Fn 
    0x0B,   // Normal 
};
const BYTE ss2_B3[] = 	// F7  
{
    0xD6,   // Fn 
    0x80,   // Normal 
};
const BYTE ss2_B4[] = 	// F8  
{
    0xD7,   // Fn 
    0x0A,   // Normal 
};
const BYTE ss2_B5[] = 	// F9  
{
    0xD8,   // Fn 
    0x01,   // Normal 
};
const BYTE ss2_B6[] = 	// F10  
{
    0xD9,   // Fn 
    0x09,   // Normal 
};
const BYTE ss2_B7[] = 	// F11  
{
    0xDA,   // Fn 
    0x78,   // Normal 
};
const BYTE ss2_B8[] = 	// F12  
{
	0xDB,   // Fn 
	0x07,   // Normal 
};
const BYTE ss2_B9[] = 	// Fn +ESC  
{
    0xDC,   // Fn       //MARTINH026:open
	0x76,   // Normal 
};
const BYTE ss2_BA[] = 	// Fn + UP  
{
    0x98,   // Normal 
	0x98
};
const BYTE ss2_BB[] = 	// Fn +DN  
{
    0x99,   // Normal 
	0x99,   // Normal 
};
const BYTE ss2_BC[] = 	// Fn + Left
{
    0x9A,   // Normal 
  	0x9A,   // Normal 
};
const BYTE ss2_BD[] = 	// Fn + Right  
{
    0x9B,   // Normal 
 	0x9B,   // Normal 
};
const BYTE ss2_BE[] = 	// Fn +Ins
{
    0x55,   // Normal 
    0xE1,   // Fn 
};
const BYTE ss2_BF[] = 	// Fn +Del
{
    0x4E,   // Normal 
    0xE2,   // Fn 
};
const BYTE ss2_C0[] = 	// Fn + R
{
    0x2D,   // Normal 
    0xE3,   // Fn 
};
const BYTE ss2_C1[] = 	// F1
{
    0x05,   // Normal 
    0xD0,   // Fn 
};

const BYTE ss2_C2[] = 	// F2 	 
{
    0x06,   // Normal 
    0xD1,   // Fn 
};

const BYTE ss2_C3[] = 	// F3  
{
    0x04,   // Normal 
    0xD2,   // Fn 
};

const BYTE ss2_C4[] =	// F4   
{
    0x0C,   // Normal 
    0xD3,   // Fn 
};

const BYTE ss2_C5[] = 	// F5  
{
    0x03,   // Normal 
	0x03,   // Fn 
};

const BYTE ss2_C6[] = 	// F6  
{
    0x0B,   // Normal 
    0xD5,   // Fn 
};

const BYTE ss2_C7[] = 	// F7  
{
    0x80,   // Normal 
    0xD6,   // Fn 
};

const BYTE ss2_C8[] = 	// F8  
{
    0x0A,   // Normal 
    0xD7,   // Fn 
};

const BYTE ss2_C9[] = 	// F9  
{
    0x01,   // Normal 
    0xD8,   // Fn 
};

const BYTE ss2_CA[] = 	// F10  
{
    0x09,   // Normal 
    0xD9,   // Fn 
};

const BYTE ss2_CB[] = 	// F11  
{
    0x78,   // Normal 
    0xDA,   // Fn 
};

const BYTE ss2_CC[] = 	// F12  
{
    0x07,   // Normal 
    0xDB,   // Fn 
};

const BYTE ss2_CD[] = 	// Fn + Space
{
	0x29,   // Normal 
    0xE4,   // Fn 
};

/* ----------------------------------------------------------------------------
 * FUNCTION: sskey2_A2_table
 *
 * The A2_TABLE structure contains the following.
 *
 * BYTE comb;  Bit   Setting Combination Key
 *            ---   -----------------------
 *             7    reserved
 *             6    reserved
 *             5    Fn
 *             4    Numlock
 *             3    Ctrl
 *             2    Alt
 *             1    Shift
 *             0    reserved
 *
 * BYTE *pntr; Pointer to array for key.
 * ------------------------------------------------------------------------- */

const A2_TABLE sskey2_A2_table[] =
{                                           /* Keyboard matrix index */
	/* Keypad --> */
	{0x10, ss2_9C },    /* index = 00h */ 	// 0x9C	//REJERRY004:Modify Numpad key table start.
    {0x10, ss2_9D },    /* index = 01h */	// 0x9D
    {0x10, ss2_9E },    /* index = 02h */	// 0x9E	
    {0x10, ss2_9F },    /* index = 03h */	// 0x9F	
    {0x10, ss2_A0 },    /* index = 04h */	// 0xA0
    {0x10, ss2_A1 },    /* index = 05h */	// 0xA1
    {0x10, ss2_A2 },    /* index = 06h */	// 0xA2
    {0x10, ss2_A3 },    /* index = 07h */	// 0xA3
    {0x10, ss2_A4 },    /* index = 08h */	// 0xA4
    {0x10, ss2_A5 },    /* index = 09h */	// 0xA5
    {0x10, ss2_A6 },    /* index = 0Ah */	// 0xA6
    {0x10, ss2_A7 },    /* index = 0Bh */	// 0xA7
    {0x10, ss2_A8 },    /* index = 0Ch */	// 0xA8
    {0x10, ss2_A9 },  	/* index = 0Dh */	// 0xA9
    {0x10, ss2_AA },  	/* index = 0Eh */	// 0xAA //REJERRY004:Modify Numpad key table end.
    {0x10, ss2_AB },   	/* index = 0Fh */	// 0xAB //REJERRY008:modify Numpad key function for Y510.
    {0x10, ss2_AC },  	/* index = 10h */	// 0xAC //REJERRY008:modify Numpad key function for Y510.
	/* Keypad <-- */
	
	/* F1~F12 hotkeys --> */
    {0x20, ss2_AD },    /* index = 11h */	// 0xAD
    {0x20, ss2_AE },    /* index = 12h */	// 0xAE
    {0x20, ss2_AF },    /* index = 13h */	// 0xAF
    {0x20, ss2_B0 },    /* index = 14h */	// 0xB0
    {0x20, ss2_B1 },    /* index = 15h */	// 0xB1
    {0x20, ss2_B2 },    /* index = 16h */	// 0xB2
    {0x20, ss2_B3 },    /* index = 17h */	// 0xB3
    {0x20, ss2_B4 },    /* index = 18h */	// 0xB4
    {0x20, ss2_B5 },  	/* index = 19h */	// 0xB5
    {0x20, ss2_B6 },  	/* index = 1Ah */	// 0xB6
    {0x20, ss2_B7 },   	/* index = 1Bh */	// 0xB7
	{0x20, ss2_B8 },    /* index = 1Ch */	// 0xB8	
    /* F1~F12 hotkeys <-- */

	{0x20, ss2_B9 },     /* index = 1Dh */	// 0xB9
	{0x20, ss2_BA},      /* index = 1Eh */	// 0xBA
	{0x20, ss2_BB },     /* index = 1Fh */	// 0xBB
	{0x20, ss2_BC },     /* index = 20h */	// 0xBC
	{0x20, ss2_BD } ,    /* index = 21h */	// 0xBD
	{0x20, ss2_BE } ,    /* index = 22h */	// 0xBE
	{0x20, ss2_BF } ,    /* index = 23h */	// 0xBF
	{0x20, ss2_C0 } ,    /* index = 24h */	// 0xBD
	{0x20, ss2_C1 } ,    /* index = 25h */	// 0xC1
	{0x20, ss2_C2 } ,    /* index = 26h */	// 0xC2
	{0x20, ss2_C3 } ,    /* index = 27h */	// 0xC3
	{0x20, ss2_C4 } ,    /* index = 28h */	// 0xC4
	{0x20, ss2_C5 } ,    /* index = 29h */	// 0xC5
	{0x20, ss2_C6 } ,    /* index = 2Ah */	// 0xC6
	{0x20, ss2_C7 } ,    /* index = 2Bh */	// 0xC7
	{0x20, ss2_C8 } ,    /* index = 2Ch */	// 0xC8
	{0x20, ss2_C9 } ,    /* index = 2Dh */	// 0xC9
	{0x20, ss2_CA } ,    /* index = 2Eh */	// 0xCA
	{0x20, ss2_CB } ,    /* index = 2Fh */	// 0xCB
	{0x20, ss2_CC } ,    /* index = 30h */	// 0xCC     	
	{0x20, ss2_CD } ,    /* index = 31h */	// 0xCD 
};
 
/*
 * ****************************************************************************
 * FUNCTION: sskey2_overlay_table
 * ****************************************************************************
 */
//REJERRY004:Modify sskey2 table start.
const BYTE sskey2_overlay_table[] =
{/* Normal   	Fn   Keyboard matrix index */
	0x05,0xD0,	// E0H    F1 <-> Mute 
	0x06,0xD1,	// E1H	F2 <-> Vol Down 
	0x04,0xD2,	// E2H	F3 <-> Vol Up   
	0x0C,0xD3,  // E3H    F4 <-> Mic            
	0x03,0xD4,	// E4H    F5 <-> Reflash 	  	 	
	0x0B,0xD5,  // E5H    F6 <-> Touchpad
	0x80,0xD6,  // E6H    F7 <-> Airplane
	0x0A,0xD7,  // E7H    F8 <-> Camera         
	0x01,0xD8,  // E8H    F9 <-> Screen Lock         
	0x09,0xD9,  // E9H    F10 <-> Display mode
	0x78,0xDA,	// EAH    F11 <-> Brightness Down         
	0x07,0xDB,	// EBH    F12 <-> Brightness Up  
	0x9B,0x95,  // ECH   	RightArrow <-> End    	 
	0x98,0x96,	// EDH	UpArrow <-> PgUp   
	0x99,0x97,	// EEH	DnArrow <-> PgDn 
	0x9A,0x94,	// EFH	LeftArrow <-> Home
	0xC0,0xC0,	// F0H	Delete 
	0xE5,0xE5,  // F1H	Video(Y510) 	
	0x42,0xC6,  // F2H      C <-> ScrLK  //REJERRY006:add.	//XITING0003:modify normal function 0x21( C ) t0 0x42( K ) 
	0x1B,0xC1,  // F3h     S <-> SysRq  //REJERRY006:add.
	0x29,0xE4, // F4h    Fn+Space  //REJERRY008:add.
	0x25,0xE9, // F5h    Fn+4		//THOMASY014:change 0x4E,0xDE to 0x25,0xE9
	0x32,0x92, // F6h    B <-> Break //THOMASY014:change 0x79,0xDF to 0x32,0x92
	0x4D,0x91, // F7h 	  P <-> Pause //THOMASY014:change 0x7B,0xE0 to 0x4D,0x91
	0xC3,0xC3, // F8h  			//XITING0057:change from 0x94/0x91 to 0xC3
	0x15,0xEA, 	// F9h 	   		//XITING0056:add  Fn+Q = FanCooling
	0x97,0x97,  // FAh     
	0x95,0x92,	// FBh	 
	0xDC,0x76,	// FCh   
	0x29,0xE4,	// FDh  
	0x5A,0x81,	// FEh   
	0xC5,0xC5,	// FFh
};
/*THOMASY014: S-
const BYTE sskey2_overlay_table1[] =
{ 
    0xD0,0x05,	// E0H    Mute <-> F1     	 
	0xD1,0x06,	// E1H	Vol Down <-> F2	  	 
	0xD2,0x04,	// E2H	Vol Up <-> F3	  	   
	0xD3,0x0C,  // E3H    Mic <-> F4            
	0xD4,0x03,	// E4H    Reflash <-> F5 	  	 	
	0xD5,0x0B,  // E5H    Touchpad <-> F6
	0xD6,0x80,  // E6H    Airplane <-> F7
	0xD7,0x0A,  // E7H    Camera <-> F8           
	0xD8,0x01,  // E8H    Screen Lock <-> F9        
	0xD9,0x09,  // E9H    Display mode <-> F10           
	0xDA,0x78,	// EAH    Brightness Down <-> F11 	                
	0xDB,0x07,  // EBH    Brightness Up <-> F12	  	  
	0x9B,0x95,  // ECH    RightArrow <-> End   	 
	0x98,0x96,	// EDH	UpArrow <-> PgUp   
	0x99,0x97,	// EEH	DnArrow <-> PgDn  
	0x9A,0x94,	// EFH	LeftArrow <-> Home  	
	0xC0,0xC0, 	// F0H	Delete
	0xE5,0xE5,  // F1H   Video(Y510)	  	
	0x21,0xC6,  // F2H   C <-> ScrLK  //REJERRY006:add.
	0x1B,0xC1,  // F3h   S <-> SysRq  //REJERRY006:add.	 
	0x29,0xE4,  // F4h   Fn+Space  //REJERRY008:add.					 
	0xDE,0x4E,  // F5h 	 	  	 
	0x79,0xDF, 	// F6h 				  
	0x7B,0xE0,  // F7h 		 			 
	0x91,0x94, 	// F8h			  
	0x96,0x96,  // F9h 	
	0x97,0x97,  // FAh  
	0x95,0x92, 	// FBh     
	0x76, 0xDC,	// FCh
	0x29,0xE4,	// FDh  
	0x81,0x5A, 	// FEh    
	0xC5, 0xC5,	// FFh
};*///*THOMASY014: E-
//REJERRY004:Modify sskey2 table end.						
/*
 * ****************************************************************************
 * FUNCTION: sskey3_80_table - Software Key Number 2
 * 80h - BFh   Pre-Index for generation Scan Code, Set2
 * ****************************************************************************
 */
const BYTE sskey3_80_table[] =
{
    /* Index from keyboard matrix */
									// Keyboard matrix index
	0x83, 	DO_SIMPLE_CODE,       	// [80h] F7 (118)
	0x5A, 	DO_E0_PREFIX_CODE,    	// [81h] Numpad Enter (108)
    0x1F, 	DO_E0_PREFIX_CODE,    	// [82h] Windows Left
    0x27, 	DO_E0_PREFIX_CODE,    	// [83h] Windows Right
    0x2F, 	DO_E0_PREFIX_CODE,    	// [84h] App(THOMASY015: change 0x2F(App) to 0x7C(PrtSc))	//XITING0057:modify from  0x7C to 0x2F.
    0x37, 	DO_E0_PREFIX_CODE,    	// [85h] Power event
    0x3F, 	DO_E0_PREFIX_CODE,    	// [86h] Sleep event
    0x5E, 	DO_E0_PREFIX_CODE,		// [87h] Wake event
    LShift, DO_CONTROL_EFFECT,		// [88h] 12 Shift(L)
    RShift, DO_CONTROL_EFFECT,		// [89h] 59 Shift(R)
    LAlt, 	DO_CONTROL_EFFECT,    	// [8Ah] 11 Alt(L)
    RAlt, 	DO_CONTROL_EFFECT_E0,	// [8Bh] E0 11 Alt(R)
    LCtrl, 	DO_CONTROL_EFFECT, 		// [8Ch] 14 Crtl(L)
    RCtrl, 	DO_CONTROL_EFFECT_E0,	// [8Dh] E0 14 Ctrl(R)
    FN, 	DO_CONTROL_EFFECT,    	// [8Eh] Fn
    OVLAY,	DO_CONTROL_EFFECT,		// [8Fh] Overlay
	0x4A, 	DO_E0_PREFIX_CODE,      // [90h] Reserved  msmart "key pad /"//JERRYCR037:Add keybaord "/" function.//JERRYCR061: Modify keyboard matrix for MFG.
    0x00, 	DO_SPECIAL_CODE,      	// [91h] Pause (126)
    0x01, 	DO_SPECIAL_CODE,      	// [92h] Break
    0x84, 	DO_SIMPLE_CODE,       	// [93h] (124) Alt-Case (SysRq)
	0x6C, 	DO_E0_PREFIX_CODE,    	// [94h] Home
    0x69, 	DO_E0_PREFIX_CODE,    	// [95h] End
    0x7D, 	DO_E0_PREFIX_CODE,  	// [96h] Page up
    0x7A, 	DO_E0_PREFIX_CODE,    	// [97h] Page down
	0x75, 	DO_E0_PREFIX_CODE,    	// [98h] UP arrow
    0x72, 	DO_E0_PREFIX_CODE,    	// [99h] Down arrow
    0x6B, 	DO_E0_PREFIX_CODE,  	// [9Ah] Left arrow
    0x74, 	DO_E0_PREFIX_CODE,   	// [9Bh] Right arrow
    
    /* For MicroSoft enhance keyboard feature. */
 	0x4D, DO_E0_PREFIX_CODE,    	// [9Ch] Next Track event
    0x15, DO_E0_PREFIX_CODE,    	// [9Dh] Prev Track event
    0x3B, DO_E0_PREFIX_CODE,    	// [9Eh] Stop event
    0x34, DO_E0_PREFIX_CODE,    	// [9Fh] Play/Pause event
    0x23, DO_E0_PREFIX_CODE,    	// [A0h] Mute event
    0x32, DO_E0_PREFIX_CODE,    	// [A1h] Volume Up event
    0x21, DO_E0_PREFIX_CODE,    	// [A2h] Volume Down event
    0x48, DO_E0_PREFIX_CODE,    	// [A3h] Mail event
    0x10, DO_E0_PREFIX_CODE,    	// [A4h] Search event
    0x3A, DO_E0_PREFIX_CODE,    	// [A5h] Web/Home event
    0x38, DO_E0_PREFIX_CODE,    	// [A6h] Back event
    0x30, DO_E0_PREFIX_CODE,    	// [A7h] Forward event
    0x28, DO_E0_PREFIX_CODE,    	// [A8h] Stop event
    0x20, DO_E0_PREFIX_CODE,    	// [A9h] Refresh event
    0x18, DO_E0_PREFIX_CODE,    	// [AAh] Favorites event
    0x2B, DO_E0_PREFIX_CODE,    	// [ABh] Caluator event
    0x40, DO_E0_PREFIX_CODE,    	// [ACh] My Computer event
    0x50, DO_E0_PREFIX_CODE,    	// [ADh] Media event
    0x00, DO_SIMPLE_CODE,       	// [AEh] Reserved
    0x00, DO_SIMPLE_CODE,      		// [AFh] Reserved

    /* Index from sskey2_A2_table */
	0x6C, DO_SIMPLE_CODE,     		// Numpad 7 Home	[B0h]
  	0x75, DO_SIMPLE_CODE,      		// Numpad 8 UP  	[B1h]
 	0x7D, DO_SIMPLE_CODE,       	// Numpad 9 PGUp	[B2h]
  	0x7C, DO_SIMPLE_CODE,       	// Numpad *   		[B3h]
	0x6B, DO_SIMPLE_CODE,       	// Numpad 4 Left	[B4h]
 	0x73, DO_SIMPLE_CODE,       	// Numpad 5 		[B5h]
	0x74, DO_SIMPLE_CODE,       	// Numpad 6 Right	[B6h]
	0x7B, DO_SIMPLE_CODE,       	// Numpad -  		[B7h]
	0x69, DO_SIMPLE_CODE,       	// Numpad 1 End		[B8h]
 	0x72, DO_SIMPLE_CODE,       	// Numpad 2 Down	[B9h]
	0x7A, DO_SIMPLE_CODE,       	// Numpad 3 PGDn	[BAh]
	0x79, DO_SIMPLE_CODE,       	// Numpad + 		[BBh]
	0x70, DO_SIMPLE_CODE,       	// Numpad 0 Ins		[BCh]
	0x71, DO_SIMPLE_CODE,      	 	// Numpad . Del		[BDh]
	0x4A, DO_E0_PREFIX_CODE, 		// Numpad /      	[BEh]
	0x00, DO_SIMPLE_CODE,      		// Reserved 		[BFh]

    0x71, DO_E0_PREFIX_CODE,  		// Delete 		[C0h]
    0x84, DO_SIMPLE_CODE,    		// SysRq			[C1h]
    0x70, DO_E0_PREFIX_CODE,    	// Insert			[C2h]
    0x7C, DO_E0_PREFIX_CODE,  		// Print Screen	[C3h]
	0x41, DO_E0_PREFIX_CODE,     	// Euro Sign 		[C4h]
	0x49, DO_E0_PREFIX_CODE,    	// Dollar Sign 		[C5h]
	0x7E, DO_SIMPLE_CODE,      		// ScrLK 			[C6h]  //REJERRY006:add.
	0x00, DO_SIMPLE_CODE,      		// Nerve Center 	[C7h]  //REJERRY008:add  key function for Y510.
	0x00, DO_SIMPLE_CODE,      		// Reserved 		[C8h]
	0x00, DO_SIMPLE_CODE,      		// Reserved 		[C9h]
	0x00, DO_SIMPLE_CODE,      		// Reserved 		[CAh]
	0x00, DO_SIMPLE_CODE,      		// Reserved 		[CBh]
	0x00, DO_SIMPLE_CODE,      		// Reserved 		[CCh]
	0x00, DO_SIMPLE_CODE,      		// Reserved 		[CDh]
	0x00, DO_SIMPLE_CODE,      		// Reserved 		[CEh]
	0x00, DO_SIMPLE_CODE,      		// Reserved 		[CFh]

    /* Function key F1 ~ F12 */
    0	, DO_COSTOMER_FUNCTION,		// Function key F1	[D0h]
    1	, DO_COSTOMER_FUNCTION,		// Function key F2	[D1h]
    2	, DO_COSTOMER_FUNCTION,		// Function key F3	[D2h]
    3	, DO_COSTOMER_FUNCTION,		// Function key F4	[D3h]
    4	, DO_COSTOMER_FUNCTION,		// Function key F5	[D4h]
    5	, DO_COSTOMER_FUNCTION,		// Function key F6	[D5h]
    6	, DO_COSTOMER_FUNCTION,		// Function key F7	[D6h]
    7	, DO_COSTOMER_FUNCTION,		// Function key F8	[D7h]
    8	, DO_COSTOMER_FUNCTION,		// Function key F9	[D8h]
    9	, DO_COSTOMER_FUNCTION,		// Function key F10	[D9h]
    10	, DO_COSTOMER_FUNCTION,		// Function key F11	[DAh]
    11	, DO_COSTOMER_FUNCTION,		// Function key F12	[DBh]
	12	, DO_COSTOMER_FUNCTION,   	// Function key Esc	[DCh]
	13	, DO_COSTOMER_FUNCTION,   	// Function key Up arrow	[DDh]
	14	, DO_COSTOMER_FUNCTION,   	// Function key Down arrow	[DEh]
	15	, DO_COSTOMER_FUNCTION,  	// Function key Left arrow	[DFh]
	16	, DO_COSTOMER_FUNCTION,  	// Function key Right arrow	[E0h]
	17	, DO_COSTOMER_FUNCTION,  	//Function key Plus[E1h]
	18	, DO_COSTOMER_FUNCTION,  	// Function key Minus[E2h]
	19	, DO_COSTOMER_FUNCTION,  	// Function key R crissis[E3h]
	32	, DO_COSTOMER_FUNCTION,  	// Function key Fn+Space[E4h]
	33  , DO_COSTOMER_FUNCTION,     // Function key Video[E5h] (Y510) //REJERRY004:add video hotkey.
	34  , DO_COSTOMER_FUNCTION,     // Function key Nerve Center[E6h](Y510) //REJERRY037:add  key function for Y510.
	35  , DO_COSTOMER_FUNCTION,	    // Function key Setting [E7h](Y520)		//THOMASY014:add
	36  , DO_COSTOMER_FUNCTION,	    // Function key Bluetooth [E8h](Y520) 	//THOMASY014:add
	37  , DO_COSTOMER_FUNCTION,	    // Function key Fn+4 = Sleep [E9h](Y520)//THOMASY014:add
	38  , DO_COSTOMER_FUNCTION,	    // Function key Fn+Q = FanCooling [EAh](Y520)			//XITING0056:add
};

/**
 * ****************************************************************************
 * The function of hotkey Fn + ins
 *
 * @return
 *
 * @parameter
 * table_entry, value of keyboard matrix table. for example Rc_ROM_Tables[]
 * event, key MAKE_EVENT or BREAK_EVENT or REPEAT_EVENT
 *
 * ****************************************************************************
 */
//-----------------------------------------------------------------------------
void CheckKBS3Wake(BYTE BKSI,BYTE BKSO)
{

}

void Et_CheckKBS3Wake(BYTE BKSI,BYTE BKSO)
{
}
/**
 * ****************************************************************************
 * The function of hotkey Fn + ins
 *
 * @return
 * 0xFF, Send_Key function will be break; (no any scan code to host)
 *
 * @parameter
 *
 * ****************************************************************************
 */
BYTE OEM_Hook_Skip_Send_Key(void)
{
    return(0x00);
}

/**
 * ****************************************************************************
 * Keyboard hook function (KSO0 - KSO15)
 *
 * @return
 *
 * @parameter
 * KSIValus, keyboard KSI
 * KSOValus, keyboard KSO
 *
 * ****************************************************************************
 */
void Hook_keyboard(BYTE KSIValus, BYTE KSOValus)
{

}		

/**
 * ****************************************************************************
 * Keyboard hook function (KSO16 - KSO17 and GPIO KSO)
 *
 * @return
 *
 * @parameter
 * KSIValus, keyboard KSI
 * KSOValus, keyboard KSO
 *
 * ****************************************************************************
 */
void Et_Hook_keyboard(BYTE KSIValus, BYTE KSOValus)
{

}

/**
 * ****************************************************************************
 * FUNCTION: Hook_Setup_Scanner_Pntr - to define the possible scanner tables
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void Hook_Setup_Scanner_Pntr(void)
{  
	//REJERRY008:Add command to identify keyboard of Y510 and IP710.
	//XITING0057:S  remove only Y530
	/*
	if(KeyBoardID == 0x01) //Y510
	{
	*/
	//XITING0057:E
		//REJERRY004:Modify to identify UK/JAP table.
		//if((cKBStatus & 0x03)== 0x00) //REJERRY089:remove.
		if((cKBStatus & 0x03)!= 0x03) //REJERRY089:add.
		{
			Scanner_Table_Pntr = (const CBYTE *) &Rc_ROM_Tables_Y510;//15" US,UK,JP
			Extendkey_Table_Pntr = (const CBYTE *) &EtKey_ROM_Tables;
		}
		//REJERRY089:S-.
		/*else if(((cKBStatus & 0x03)== 0x01)||((cKBStatus & 0x03)== 0x02))
		{
			Scanner_Table_Pntr = (const CBYTE *) &Rc_ROM_Tables_15UK_Y510;//15" UK,JAP.
			Extendkey_Table_Pntr = (const CBYTE *) &EtKey_ROM_Tables;
		}*/
		//REJERRY089:E-.
		else 
		{
	    	Scanner_Table_Pntr = (const CBYTE *) &Rc_ROM_Tables_15BR_Y510;//15" Brazil.
			Extendkey_Table_Pntr = (const CBYTE *) &EtKey_ROM_Tables;
		}
		//REJERRY004:Modify end.
	//XITING0057:S  remove only Y530
	/*
	}
	else //IP710
	{
		if((cKBStatus & 0x03)== 0x00)
		{
			Scanner_Table_Pntr = (const CBYTE *) &Rc_ROM_Tables_IP710;//15" US
			Extendkey_Table_Pntr = (const CBYTE *) &EtKey_ROM_Tables;
		}
		else if(((cKBStatus & 0x03)== 0x01)||((cKBStatus & 0x03)== 0x02))
		{
			Scanner_Table_Pntr = (const CBYTE *) &Rc_ROM_Tables_15UK_IP710;//15" UK,JAP.
			Extendkey_Table_Pntr = (const CBYTE *) &EtKey_ROM_Tables;
		}
		else 
		{
	    	Scanner_Table_Pntr = (const CBYTE *) &Rc_ROM_Tables_15BR_IP710;//15" Brazil.
			Extendkey_Table_Pntr = (const CBYTE *) &EtKey_ROM_Tables;
		}
	}
	*/
	//XITING0057:E
	//REJERRY008:Add command to identify keyboard of Y510 and IP710.
}

//-----------------------------------------------------------------------------
// The function of setting GPIO scan pin to high
//-----------------------------------------------------------------------------
void Hook_SetGPIOScanPinH(void)
{
	if(ExternMatrixGPO)
	{
}
}
/**
 * ****************************************************************************
 * The function of setting GPIO scan pin to low
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void Hook_SetGPIOScanPinL(void)
{
	if(ExternMatrixGPO)
	{
}
}
/**
 * ****************************************************************************
 * The function of setting GPIO scan pin output
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void Hook_SetGPIOScanPinCtrl(void)
{
	if(ExternMatrixGPO)
	{
}
}
/**
 * ****************************************************************************
 * Fn key make
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void Hook_Fn_Key_Make(void)
{
   if ( IS_MASK_SET(cCmd, b6TestBtnEn) )
	{
   		Buffer_Key(0xE0);                   //
       	Buffer_Key(0x16);              		// page down make
   		F_Service_SEND = 1;
}
	FnStatus = 1;	
}
/**
 * ****************************************************************************
 * Fn key break
 *
 * @return
 *
 * @parameter
 *
 * ****************************************************************************
 */
void Hook_Fn_Key_Break(void)
{
	//REJERRY004:S+ for "Display mode" hotkey scancode send control.
	if ( IS_MASK_SET(SysStatus, FnF3WinKeyDn) ) //FnF3PKeyUp
	{
		if(IS_MASK_CLEAR(SysStatus, FnF3PKeyUp))
		{
			simple_code(0x4D,BREAK_EVENT);	// P Key.
		}
		e0_prefix_code(0x1F,BREAK_EVENT);	// Win Key.
	
		SysStatus &= 0xF3;	// Clear Win+P Key.
	
		F_Service_SEND = 1;
		RamDebug(0x04);
	}
	//REJERRY004:E+ for "Display mode" hotkey scancode send control.
	
	if ( IS_MASK_SET(cCmd, b6TestBtnEn) )
	{
		Buffer_Key(0xE0);					//
		Buffer_Key(0xF0);					//
		Buffer_Key(0x16);					// page down make
		F_Service_SEND = 1;
}
	FnStatus = 0;							// for factory

}
//AIUU3_W19:<<<<<
//-----------------------------------------------------------------------------
// Return : 0xFF --> sskey2_A2_table contains bit6
//-----------------------------------------------------------------------------
BYTE Hook_calc_index_comb_BIT6(void)
{
    return(0x00);
}

/**
 * ****************************************************************************
 *
 *
 * @return
 * 0xFF, sskey2_A2_table contains bit7
 *
 * @parameter
 *
 * ****************************************************************************
 */
BYTE Hook_calc_index_comb_BIT7(void)
{
    return(0x00);
}

//HEGANG005:s+Optimize video key method follow lenovo and Synchronous state of TP.

/**
 * ****************************************************************************
 * hook function for Lenove never center vedio record
 * 
 * @return
 *
 * @parameter
 * u8Protocol, 0 boot mode, 1, report mode
 *
 * ****************************************************************************
 */
void Hook_Lenovo_Vedio_Record(void)
{
 if(IS_MASK_SET(Vedio_Record_Key_Reg,BIT0))
    {
     if(Vedio_Record_Key_Delay >= 6)
      {
        Vedio_Record_Key_Delay=0;
       Buffer_Key(0x14); 
        Buffer_Key(0x12);
        Buffer_Key(0x50); //F22
      
        CLEAR_MASK(Vedio_Record_Key_Reg,BIT0);
        SET_MASK(Vedio_Record_Key_Reg,BIT1);
      }
     else
      {
         Vedio_Record_Key_Delay++;
      }   
    }
   
   if(IS_MASK_SET(Vedio_Record_Key_Reg,BIT1))
    {
     if(Vedio_Record_Key_Delay >= 3)
      {
        Vedio_Record_Key_Delay=0;
         Buffer_Key(0xF0);      
        Buffer_Key(0x14);
		Buffer_Key(0xF0);
       Buffer_Key(0x12); 
	   Buffer_Key(0xF0);
        Buffer_Key(0x50); //F22
        CLEAR_MASK(Vedio_Record_Key_Reg,BIT1);
      }
     else
      {
         Vedio_Record_Key_Delay++;
      }
    }
}
//HEGANG005:e+Optimize video key method follow lenovo and Synchronous state of TP.

