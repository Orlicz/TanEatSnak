//Includes
#include<bits/stdc++.h>
using namespace std;
//Defines
#define ten(x) (((x)<<1)+((x)<<3))
#define opposite(x) ((~(x))+1)
#define Fsize 100000
#ifdef ONLINE_JUDGE
#define getchar() (A==B&&(B=(A=Fin)+fread(Fin,1,Fsize,stdin),A==B)?EOF:*A++)
#define putchar(Ch) (FoutSize<Fsize?Fout[FoutSize++]=Ch:(fwrite(Fout,1,Fsize,stdout),Fout[(FoutSize=0)++]=Ch))
#define inline __inline__ __attribute__((always_inline)) 
#endif
#define register 
//Requires
template<typename T>concept Double = std::is_same<T, float>::value || std::is_same<T, double>::value || std::is_same<T, long double>::value;
template<typename T>concept Int = std::is_integral<T>::value;
//Vars
template<typename T = long long> constexpr T Pow10[10] = { 10,100,1000,10000,100000,1000000,10000000,100000000,1000000000,10000000000 };
static struct ArrayWriter { char Insert = ' ', End = '\n'; }war;
template<typename T = char> struct VectorIOer { T* x; int Len; template<typename Other>inline VectorIOer<Other>& operator()(Other* x, int Len) { VectorIOer<Other> e; e.Len = Len, e.x = x; return e; } }; VectorIOer vio;
int Index, Top, FoutSize; char Ch, * A, * B, Fin[Fsize], Fout[Fsize], Stack[Fsize];
//Functions
template<Int T> inline void read(register T& x) { bool sign = 0; x = 0; while (!((Ch = getchar()) == '-' ? Ch = getchar(), sign = 1 : isdigit(Ch))); while (x = ten(x) + (Ch & 15), isdigit(Ch = getchar())); x = sign ? opposite(x) : x; }
template<Double T> inline void read(register T& x) { bool sign = 0; x = 0, Index = 1; while (!((Ch = getchar()) == '-' ? Ch = getchar(), sign = 1 : isdigit(Ch))); while (x = 10 * x + (Ch & 15), isdigit(Ch = getchar())); if (Ch == '.' && (Ch = getchar())) while (x += T(Ch & 15) / (Index *= 10), isdigit(Ch = getchar())); x = sign ? -x : x; }
inline void read(register char& x) { x = getchar(); }
inline void read(register char* x) { while ((*(x++) = getchar()) != '\n'); *(--x) = '\0'; }
template<size_t Len, typename T> inline void read(T* x) { Index = 0; while (read(*(x + Index++)), Index != Len); }
template<typename T> inline void read(register VectorIOer<T>&& io) { Index = 0; while (read(*(io.x + Index++)), Index != io.Len); }
template<typename T> inline void read(register VectorIOer<T>& io) { Index = 0; while (read(*(io.x + Index++)), Index != io.Len); }
template<typename T, typename... Args>inline void read(register T& x, register Args&... args) { read(x), read(args...); }
template<Int T> inline void write(register T x) { if (!x)return (void)(putchar('0')); if (x < 0)putchar('-'), x = -x; while (x)Stack[++Top] = (x % 10) ^ 48, x /= 10; while (Top)putchar(Stack[Top--]); }
inline void write(register char& x) { putchar(x); }
inline void write(register char* x) { while (putchar(*(x++)), *x ^ '\0'); }
inline void write(const char x[]) { register int i = 0; while (putchar(x[i++]), x[i] ^ '\0'); }
template<size_t Len, typename T> inline void write(T* x) { Index = 0; while (write(*(x + Index++)), Index != Len) putchar(war.Insert); putchar(war.End); }
template<typename T> inline void write(register VectorIOer<T>&& io) { Index = 0; while (write(*(io.x + Index++)), Index != io.Len) putchar(war.Insert); putchar(war.End); }
template<typename T> inline void write(register VectorIOer<T>& io) { Index = 0; while (write(*(io.x + Index++)), Index != io.Len) putchar(war.Insert); putchar(war.End); }
template<Double T>inline void write(T X, int k = 6) { long long x = X; if (!x) (putchar('0')); if (x < 0)putchar('-'), x = -x; while (x)Stack[++Top] = (x % 10) ^ 48, x /= 10; while (Top)putchar(Stack[Top--]); if (!k) return; putchar('.'), Index = 1; if (!(X -= (long long)X))while (k--) putchar('0'); write((long long)(X * Pow10<long long>[k])); }
template<typename T, typename... Args> inline void write(register T x, register Args... args) { write(x), write(args...); }
inline int clear() { fwrite(Fout, 1, FoutSize, stdout); return FoutSize = 0; }
long long p, a, b;
#define ll long long
int exgcdd(int a, int b, int& x, int& y)
{
	if (b == 0) {
		x = 1, y = 0;
		return a;
	}
	int r = exgcdd(b, a % b, x, y);
	int t = x;
	x = y;
	y = t - a / b * y;
	return r;
}
int inv(int n, int m)
{
	int x, y;
	int ans = exgcdd(n, m, x, y);
	if (ans == 1)
		return (x % m + m) % m;
	//定义：正整数 a, n，如果有 ax ≡ 1(mod n)，则称 x 的最小整数解为 a 模 n的逆元。
	else
		return -1;
}


template<Int ll>
ll inv(ll a, ll p) {
	ll d, x, y;
	exgcd(a, p, d, x, y);
	return d == 1 ? (x + p) % p : -1;
}
template<Int T>
T power(T&& a, T&& b, T&& c) {
	if (b == 0)
		return 1 % c;
	long long ans = 1, t = a;
	while (b > 0) {
		if (b & 1) ans = ans * t % c;
		b /= 2; t = t * t % c;
	}
	return ans;
}
template<Int T>
void exgcd(T a, T b, T& x, T& y) {
	if (b == 0) {
		x = 1, y = 0;
		return;
	}
	exgcd(b, a % b, y, x);
	y -= a / b * x;
}
template<Int T, Int Y, Int P>
inline void setinv(T* inv, Y p, P go) {
	inv[1] = 1;
	for (Y i = 2; i < go; ++i)
		inv[i] = (p - p / i) * inv[p % i] % p;
}
template<Int Y>
Y powmod(Y a, Y b, Y p) {
	Y res = 1;
	while (b > 0) {
		if (b & 1) res = res * a % p;
		a = a * a % p, b >>= 1;
	}
	return res;
}

template<Int R>
int generator(R p) {
	vector<R> fact;
	R phi = p - 1, n = phi;
	for (R i = 2; i * i <= n; ++i) {
		if (n % i == 0) {
			fact.push_back(i);
			while (n % i == 0) n /= i;
		}
	}
	if (n > 1) fact.push_back(n);
	for (R res = 2; res <= p; ++res) {
		bool ok = true;
		for (R factor : fact) {
			if (powmod(res, phi / factor, p) == 1) {
				ok = false;
				break;
			}
		}
		if (ok) return res;
	}
	return -1;
}

template<Int T>
inline T bsgs(T a, T b, T p) {

	map<T, T> HashOnMap;
	HashOnMap.clear();
	b %= p;
	T t = sqrt(p) + 1;
	for (register T i = 0; i < t; ++i)
		HashOnMap[(T)b * powmod(a, i, p) % p] = i;
	a = powmod(a, t, p);
	if (!a)
		if (b == 0)
			return 1;
		else
			return -1;
	int tt__ = -1;
	for (register T i = 1; i <= t; ++i) {
		T Value = powmod(a, i, p);
		int j = (HashOnMap.find(Value) == HashOnMap.end()) ? -1 : HashOnMap[Value];
		if (j >= 0 && i * t - j >= 0) { tt__ = i * t - j; break; }
	}
	return tt__;
}
template<Int T>
T phi(T n)
{
	T res = n;
	for (T i = 2; i * i <= n; ++i)
	{
		if (n % i == 0)
			res = res / i * (i - 1); // 先除再乘防止溢出
		while (n % i == 0) // 每个质因数只处理一次，可以把已经找到的质因数除干净
			n /= i;
	}
	if (n > 1)
		res = res / n * (n - 1); // 最后剩下的部分也是原来的n的质因数
	return res;
}


int exbsgs(int a, int b, int p)
{
	if (b == 1 || p == 1)return 0;     //特殊情况，x=0时最小解
	int g = gcd(a, p), k = 0, na = 1;
	while (g > 1)
	{
		if (b % g != 0)return -1;    //无法整除则无解
		k++; b /= g; p /= g; na = na * (a / g) % p;
		if (na == b)return k;   //na=b说明前面的a的次数为0，只需要返回k
		g = gcd(a, p);
	}
	int f = bsgs(a, b * inv(na, p) % p, p);
	if (f == -1)return -1;
	return f + k;
}


inline void BSGS(ll x, ll y) {
	mp.clear();
	if (y == 1) {
		printf("0\n");
		return;
	}
	ll m = sqrt(mod), s = y;
	for (ll i = 0; i <= m; i++) {
		mp[s] = i;
		s = s * x % mod;
	}
	ll xx = ksm(x, m); s = 1;
	for (ll i = 1; i <= m; i++) {
		s = s * xx % mod;
		if (mp.count(s)) {
			if (i * m - mp[s] == 0) printf("Orz, I cannot find x!\n");
			else { write(i * m - mp[s]); putchar('\n'); }
			return;
		}
	}
	printf("Orz, I cannot find x!\n");
}
int main() {
	using ll = long long;
	int t, k;
	read(t, k);
	while (y--) {
		long long y, z, p;
		read(y, z, p);
		if (k == 1) {
			write(powmod(y,z,p),'\n');
		}
		else if (k == 2) {
			ll xx, yy;
			ll _gcd = exgcdd(y, p, xx, yy);
			if (m % _gcd) write("Orz, I cannot find x!\n");
			else {
				ll g = mod / _gcd;
				while (x < 0) x += g;
				write(((x * m / _gcd) % mod + mod) % mod); write('\n');
			}
		}
		else {
			if (y % p) BSGS(y % p, z % p);
			else printf("Orz, I cannot find x!\n");
		}
	}
}