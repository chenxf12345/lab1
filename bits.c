/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 */

#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  // 将 1 左移 31 位即可得到 0x80000000
  return 1 << 31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
  // 利用德摩根定律: x ^ y = (x | y) & ~(x & y) = ~(~x & ~y) & ~(x & y)
  return ~(x & y) & ~(~x & ~y);
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  // 算术右移 31 位：负数变成全 1 (-1/0xFFFFFFFF)，非负数变成全 0
  // -x 在补码中等于 ~x + 1
  return (~x + 1) & (x >> 31);
}

// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  int s = src << 3; // 等同于 src * 8
  int d = dst << 3; // 等同于 dst * 8
  int b = (x >> s) & 0xFF; // 提取 src 字节
  int m = ~(0xFF << d);    // 构造清空 dst 字节的掩码
  return (x & m) | (b << d);
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  // 由于右移是算术右移，我们必须把高 n 位强制清零
  // 构造掩码：最高位 1 算术右移 n 位后再左移 1 位，取反后正好是低 (32-n) 位全为 1 的掩码
  int mask = ~(1 << 31 >> n << 1);
  return (x >> n) & mask;
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  // 构造 0x0F0F0F0F 掩码
  int m = 0x0F | (0x0F << 8);
  m = m | (m << 16);
  // 高 4 位右移，低 4 位左移，最后组合
  return ((x & m) << 4) | ((x >> 4) & m);
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  // x | (x + 1) 可以把最低位的 0 变成 1，而保持其余位不变
  int x1 = x | (x + 1);
  // ~x1 & (x1 + 1) 则可以隔离出此时最新的最低位 0 (即原本的次低位 0)
  return ~x1 & (x1 + 1);
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  // 将 32 位的异或和折叠到第 0 位
  x ^= x >> 16;
  x ^= x >> 8;
  x ^= x >> 4;
  x ^= x >> 2;
  x ^= x >> 1;
  // 如果 1 的总数是偶数，异或和为 0，取反(!x)可返回 1
  return (~x) & 1;
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  // n 取模 32
  n = n & 31;
  // shift_left = 32 - n。为避免非法左移 32 位，使用 (~n + 33) & 31
  int shift_left = (~n + 33) & 31;
  // 右移部分（需转逻辑右移避免负数高位补1）
  int mask = ~(1 << 31 >> n << 1);
  return ((x >> n) & mask) | (x << shift_left);
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  // 这题非常精妙，向最近的 2^n 舍入，本质上是给 x 加上一个偏移量 (bias) 后截断低 n 位
  int n_minus_1 = n + ~0;
  int half = 1 << n_minus_1;         // 2^(n-1)
  int mask = (half << 1) + ~0;       // 2^n - 1，即低 n 位掩码
  int bit_n = (x >> n) & 1;          // 检查商的奇偶性
  // 如果商是奇数(bit_n=1)，加上 2^(n-1) 让中间值进位（向偶数舍入）；如果是偶数，加上 2^(n-1)-1，中间值不进位
  int bias = half + ~0 + bit_n; 
  return (x + bias) & ~mask;
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  int sign_x = x >> 31;
  int sign_y = y >> 31;
  int diff = x + ~y + 1;             // x - y
  int sign_diff = diff >> 31;
  // 计算 x > y 的掩码 (考虑符号不同的溢出情况)
  int mask = (~sign_x & sign_y) | (~(sign_x ^ sign_y) & ~sign_diff);
  // 常规向下取整的中点公式
  int floor_mid = (x & y) + ((x ^ y) >> 1);
  // 当 x > y 并且 x,y 一奇一偶 (中点在两个整数之间) 时，加 1
  return floor_mid + (mask & (x ^ y) & 1);
}

// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  int sx = x >> 31;
  int sa = a >> 31;
  int sb = b >> 31;
  int not_sx = ~sx;
  int not_sa = ~sa;
  int not_sb = ~sb;
  int not_x = ~x;
  
  int eq_xa = ~(sx ^ sa);
  int eq_xb = ~(sx ^ sb);
  
  // 稳健的大于等于 (>=) 比较逻辑，避免 a-b 直接相减导致溢出
  int x_ge_a = (not_sx & sa) | (eq_xa & ~((x + not_sa + 1) >> 31));
  int b_ge_x = (not_sb & sx) | (eq_xb & ~((b + not_x + 1) >> 31));
  int x_ge_b = (not_sx & sb) | (eq_xb & ~((x + not_sb + 1) >> 31));
  int a_ge_x = (not_sa & sx) | (eq_xa & ~((a + not_x + 1) >> 31));
  
  // (x >= a && b >= x) || (x >= b && a >= x)
  return ((x_ge_a & b_ge_x) | (x_ge_b & a_ge_x)) & 1;
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  int sign_x = x >> 31;
  int x4 = x << 2;
  int res = x + x4; // 5x
  int sign_res = res >> 31;
  
  // 检测上溢/下溢：如果 x>>29 不是纯符号，说明 x<<2 已经溢出
  // 或者 x 与 x4 同号但相加后变号，也是溢出
  int over = ((x >> 29) ^ sign_x) | (sign_x ^ sign_res);
  int max = ~(1 << 31);       // 0x7FFFFFFF
  int sat = sign_x ^ max;     // 如果 x 是正数，饱和为 0x7FFFFFFF；如果是负数，饱和为 0x80000000
  int mask = ~(!!over) + 1;   // 如果 overflow，mask 为全 1；否则全 0
  
  return (mask & sat) | (~mask & res);
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  // 通过符号扩展提取 64 位视角下的高 32 位
  int hx = x >> 31;
  int hy = y >> 31;
  int hz = z >> 31;
  
  int sum1 = x + y;
  // 提取进位 (carry) 的逻辑公式
  int c1 = ((x & y) | ((x | y) & ~sum1)) >> 31 & 1;
  
  int sum2 = sum1 + z;
  int c2 = ((sum1 & z) | ((sum1 | z) & ~sum2)) >> 31 & 1;
  
  // 理论上的 64 位无损加法的高 32 位结果
  int upper = hx + hy + hz + c1 + c2;
  // 正常情况下，高 32 位应该等于低 32 位的符号位
  int target = sum2 >> 31;
  
  // upper - target 刚好等于数学上所需的分类状态 (+1, 0, -1)
  return upper + ~target + 1;
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  unsigned sign = uf & 0x80000000;
  unsigned exp = (uf >> 23) & 0xFF;
  unsigned frac = uf & 0x007FFFFF;

  if (exp == 0xFF) return uf; // NaN or Inf

  if (exp == 0) { // 非规格化数
      unsigned frac3 = frac + (frac << 1); // frac * 3
      // 向偶数舍入除以 2
      unsigned new_frac = (frac3 >> 1) + ((frac3 & 3) == 3);
      return sign | new_frac; 
  }

  // 规格化数
  unsigned M = 0x00800000 | frac;
  unsigned M3 = M + (M << 1);
  
  if (M3 >= 0x02000000) {
      unsigned quo = M3 >> 2;
      unsigned rem = M3 & 3;
      frac = quo + (rem > 2 || (rem == 2 && (quo & 1)));
      exp += 1;
  } else {
      unsigned quo = M3 >> 1;
      unsigned rem = M3 & 1;
      frac = quo + (rem == 1 && (quo & 1));
  }

  // 乘后指数溢出成为 Inf
  if (exp >= 0xFF) return sign | 0x7F800000;

  return sign | (exp << 23) | (frac & 0x007FFFFF);
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  unsigned sign = uf & 0x80000000;
  unsigned exp = (uf >> 23) & 0xFF;
  unsigned frac = uf & 0x007FFFFF;

  if (exp == 0xFF) return uf;

  if (exp < 127) { // 绝对值小于 1 的情况
      if (exp == 126 && frac > 0) return sign | 0x3F800000; // 超出 0.5 进位到 1.0
      return sign; // 小于等于 0.5，舍弃为 0.0
  }

  int E = exp - 127;
  if (E >= 23) return uf; // 已经是一个整数，无小数部分可舍弃

  unsigned shift = 23 - E;
  unsigned mask = (1 << shift) - 1; // 小数部分掩码
  unsigned rem = uf & mask;
  unsigned half = 1 << (shift - 1);
  unsigned quo = (uf >> shift) & 1; // 整数部分的最低位

  // 向偶数舍入法则：大于一半，或等于一半且整数最低位是1，则进位
  if (rem > half || (rem == half && quo)) {
      uf += (1 << shift); // 直接在位级浮点表示上相加，处理阶码进位极为平滑
  }
  
  return uf & ~mask; // 清空小数残余
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  if (x == 0) return 0;
  unsigned sign = x & 0x80000000;
  unsigned ux = x;
  // 全部统一为无符号处理（0x80000000 取负仍为其自身，完美契合无符号性质）
  if (sign) ux = -x; 

  int exp = 31;
  unsigned mask = 0x80000000;
  // 寻找最高位 1
  while ((ux & mask) == 0) {
      exp--;
      mask >>= 1;
  }
  
  unsigned frac;
  if (exp <= 23) {
      frac = (ux << (23 - exp)) & 0x007FFFFF;
  } else {
      int shift = exp - 23;
      unsigned round_mask = (1 << shift) - 1;
      unsigned rem = ux & round_mask;
      unsigned half = 1 << (shift - 1);
      unsigned quo = (ux >> shift) & 1;
      
      frac = (ux >> shift) & 0x007FFFFF;
      // 尾数丢失阶段需遵守 IEEE 754 偶数舍入
      if (rem > half || (rem == half && quo)) {
          frac += 1;
          if (frac >= 0x00800000) { // 如果尾数溢出产生进位
              frac = 0;
              exp += 1;
          }
      }
  }
  return sign | ((exp + 127) << 23) | frac;
}

// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  // 分治法实现汉明重量计数 (Hamming Weight)
  int m1 = 0x55 | (0x55 << 8); m1 = m1 | (m1 << 16); // 0x55555555
  int m2 = 0x33 | (0x33 << 8); m2 = m2 | (m2 << 16); // 0x33333333
  int m4 = 0x0F | (0x0F << 8); m4 = m4 | (m4 << 16); // 0x0F0F0F0F
  x = (x & m1) + ((x >> 1) & m1);
  x = (x & m2) + ((x >> 2) & m2);
  x = (x + (x >> 4)) & m4;
  x = x + (x >> 8);
  x = x + (x >> 16);
  return x & 0x3F;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x)
{
  // 这里是最极限的操作数压榨：由于常数不能大于 255，这利用了极少的操作数来生成所有复杂的掩码
  // Lexical count total 34 ops exactly.
  int m16 = (0xFF << 8) | 0xFF;  // 0xFFFF
  int m8 = m16 ^ (m16 << 8);     // 0x00FF00FF
  int m4 = m8 ^ (m8 << 4);       // 0x0F0F0F0F
  int m2 = m4 ^ (m4 << 2);       // 0x33333333
  int m1 = m2 ^ (m2 << 1);       // 0x55555555
  
  // 按块翻转
  x = (x << 16) | ((x >> 16) & m16);
  x = ((x & m8) << 8) | ((x >> 8) & m8);
  x = ((x & m4) << 4) | ((x >> 4) & m4);
  x = ((x & m2) << 2) | ((x >> 2) & m2);
  x = ((x & m1) << 1) | ((x >> 1) & m1);
  
  return x;
}