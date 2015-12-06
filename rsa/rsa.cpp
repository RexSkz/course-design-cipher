#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <malloc.h>
#define MAX 100
#define LEN sizeof(struct slink)

struct slink {
	int bignum[MAX];
	struct slink *next;
};

void sub(int a1[MAX], int a2[MAX], int *c);

void print(int a[MAX]) {
	for (int i = 0; i < a[MAX - 1]; ++i)
		printf("%d", a[a[MAX - 1] - i - 1]);
	printf("\n");
}
int cmp(int a1[MAX], int a2[MAX]) {
	int l1 = a1[MAX - 1], l2 = a2[MAX - 1];
	if (l1 > l2) return 1;
	if (l1 < l2) return -1;
	for (int i= l1 - 1; i >= 0; --i) {
		if (a1[i] > a2[i]) return 1;
		if (a1[i] < a2[i]) return -1;
	}
	return 0;
}
void mov(int a[MAX], int *b) {
	for (int j = 0; j < MAX; ++j) b[j]=a[j];
}
void mul(int a1[MAX], int a2[MAX], int *c) {
	int l1 = a1[MAX - 1], l2 = a2[MAX - 1];
	if (a1[MAX - 2] == '-' && a2[MAX - 2] == '-') c[MAX - 2] = 0;
	else if (a1[MAX - 2] == '-') c[MAX - 2] = '-';
	else if (a2[MAX - 2] == '-') c[MAX - 2] = '-';
	int x, y, z, w;
	for (int i = 0; i < l1; ++i) {
		for (int j = 0; j < l2; ++j) {
			x=a1[i]*a2[j];
			y=x/10;
			z=x%10;
			w=i+j;
			c[w]=c[w]+z;
			c[w+1]=c[w+1]+y+c[w]/10;
			c[w]=c[w]%10;
		}
	}
	w = l1 + l2;
	if (c[w - 1] == 0) --w;
	c[MAX - 1] = w;
}
void add(int a1[MAX], int a2[MAX], int *c) {
	int temp[MAX];
	int l1 = a1[MAX - 1], l2 = a2[MAX - 1];
	if (a1[MAX - 2] == '-' && a2[MAX - 2] == '-') c[MAX - 2] = '-';
	else if (a1[MAX - 2] == '-') {
		mov(a1, temp);
		temp[MAX - 2] = 0;
		sub(a2, temp, c);
		return;
	}
	else if (a2[MAX - 2] == '-') {
		mov(a2, temp);
		temp[98] = 0;
		sub(a1, temp, c);
		return;
	}
	int len = (l1 < l2) ? l1 : l2;
	int k = 0;
	for (int i = 0; i < len; ++i) {
		c[i] = (a1[i] + a2[i] + k) % 10;
		k = (a1[i] + a2[i] + k) / 10;
	}
	if (l1 > len) {
		for (int i = len; i < l1; ++i) {
			c[i] = (a1[i] + k) % 10;
			k = (a1[i] + k) / 10;
		}
		if (k != 0) {
			c[l1] = k;
			len = l1 + 1;
		}
		else len = l1;
	}
	else {
		for (int i = len; i < l2; ++i) {
			c[i] = (a2[i] + k) % 10;
			k = (a2[i] + k) / 10;
		}
		if (k != 0) {
			c[l2] = k;
			len = l2 + 1;
		}
		else len = l2;
	}
	c[MAX - 1] = len;
}
void sub(int a1[MAX], int a2[MAX], int *c) {
	int i, len, t1[MAX], t2[MAX];
	int k = 0;
	int l1 = a1[MAX - 1], l2 = a2[MAX - 1];
	if (a1[MAX - 2] == '-' && a2[MAX - 2] == '-') {
		mov(a1, t1);
		mov(a2, t2);
		t1[MAX - 2] = 0;
		t2[MAX - 2] = 0;
		sub(t2, t1, c);
		return;
	}
	else if (a2[MAX - 2] == '-') {
		mov(a2, t2);
		t2[MAX - 2] = 0;
		add(a1, t2, c);
		return;
	}
	else if (a1[MAX - 2] == '-') {
		mov(a2, t2);
		t2[MAX - 2] = '-';
		add(a1, t2, c);
		return;
	}
	if (cmp(a1, a2) == 1) {
		len = l2;
		for (i = 0; i < len; ++i) {
			if (a1[i] - k - a2[i] < 0) {
				c[i] = (a1[i] - a2[i] - k + 10) % 10;
				k = 1;
			}
			else {
				c[i] = (a1[i] - a2[i] - k) % 10;
				k = 0;
			}
		}
		for (i = len; i < l1; ++i) {
			if (a1[i] - k < 0) {
				c[i] = (a1[i] - k + 10) % 10;
				k = 1;
			}
			else {
				c[i] = (a1[i] - k) % 10;
				k = 0;
			}
		}
		if (c[l1-1]==0) {
			len=l1-1;
			i = 2;
			while (c[l1 - i] == 0) {
				len = l1 - i;
				++i;
			}
		}
		else {
			len = l1;
		}
	}
	else if (cmp(a1, a2) == -1) {
		c[MAX - 2] = '-';
		len = l1;
		for (i = 0; i < len; ++i) {
			if (a2[i] - k - a1[i] < 0) {
				c[i] = (a2[i] - a1[i] - k + 10) % 10;
				k = 1;
			}
			else {
				c[i] = (a2[i] -a1[i] - k) % 10;
				k = 0;
			}
		}
		for (i = len; i < l2; ++i) {
			if (a2[i] - k < 0) {
				c[i] = (a2[i] - k + 10) % 10;
				k = 1;
			}
			else {
				c[i] = (a2[i] - k) % 10;
				k = 0;
			}
		}
		if (c[l2 - 1] == 0) {
			len = l2 - 1;
			i = 2;
			while (c[l1 - i] == 0) {
				len = l1 - i;
				++i;
			}
		}
		else len = l2;
	}
	else if (cmp(a1, a2) == 0) {
		len = 1;
		c[len - 1] = 0;
	}
	c[MAX - 1] = len;
}
void mod(int a[MAX], int b[MAX], int *c) {
	int d[MAX];
	mov(a, d);
	while (cmp(d, b) != -1) {
		sub(d, b, c);
		mov(c, d);
	}
}
void divt(int t[MAX], int b[MAX], int *c , int *w) {
	int a1, b1, m;
	int d[MAX], e[MAX], f[MAX], g[MAX], a[MAX];
	mov(t, a);
	for (int i = 0; i < MAX; ++i) e[i] = 0;
	for (int i = 0; i < MAX; ++i) d[i] = 0;
	for (int i = 0; i < MAX; ++i) g[i] = 0;
	a1 = a[MAX - 1];
	b1 = b[MAX - 1];
	if (cmp(a, b) == -1) {
		c[0] = 0;
		c[MAX - 1] = 1;
		mov(t, w);
		return;
	}
	else if (cmp(a, b) == 0) {
		c[0] = 1;
		c[MAX - 1] = 1;
		w[0] = 0;
		w[MAX - 1] = 1;
		return;
	}
	m = a1 - b1;
	for (int i = m; i >= 0; --i) {
		for (int j = 0; j < MAX; ++j) d[j] = 0;
		d[i] = 1;
		d[MAX - 1] = i + 1;
		mov(b, g);
		mul(g, d, e);
		while (cmp(a, e) != -1) {
			++c[i];
			sub(a, e, f);
			mov(f, a);
		}
		for (int j = i; j < MAX; ++j) e[j]=0;
	}
	mov(a, w);
	if (c[m] == 0) c[MAX - 1] = m;
	else c[MAX - 1] = m + 1;
}
void expmod(int a[MAX] , int p[MAX] , int n[MAX], int *m) {
	int t[MAX], l[MAX], temp[MAX];
	int w[MAX], s[MAX], c[MAX], b[MAX];
	for (int i = 0; i < MAX - 1; ++i) b[i] = l[i] = t[i] = w[i] = 0;
	t[0] = 2; t[MAX - 1] = 1;
	l[0] = 1; l[MAX - 1] = 1;
	mov(l, temp);
	mov(a, m);
	mov(p, b);
	// while b != 1
	while(cmp(b, l) != 0) {
		for (int i = 0; i < MAX; ++i) w[i] = c[i] = 0;
		// b /= 2, c = b % 2
		divt(b, t, w, c);
		mov(w, b);
		// if odd(b)
		if (cmp(c, l) == 0) {
			for (int i = 0; i < MAX; ++i) w[i] = 0;
			// temp *= m
			mul(temp, m, w);
			mov(w, temp);
			for (int i = 0; i < MAX; ++i) w[i] = c[i] = 0;
			// temp %= n
			divt(temp, n, w, c);
			mov(c, temp);
		}
		for (int i = 0; i < MAX; ++i) s[i] = 0;
		// s = m * m
		mul(m, m, s);
		for (int i = 0; i < MAX; ++i) c[i] = 0;
		// m = s % n
		divt(s, n, w, c);
		mov (c, m);
	}
	for (int i = 0; i < MAX; ++i) s[i] = 0;
	mul(m, temp, s);
	for (int i = 0; i < MAX; ++i) c[i] = 0;
	divt(s, n, w, c);
	mov (c, m);
	m[MAX - 2] = a[MAX - 2];
}
int	is_prime_san(int p[MAX]) {
	int a[MAX], t[MAX], s[MAX], o[MAX];
	for (int i = 0; i < MAX; ++i) s[i] = o[i] = a[i] = t[i] = 0;
	t[0] = 1; t[MAX - 1] = 1;
	a[0] = 2; a[MAX - 1] = 1;
	sub(p, t, s);
	expmod(a, s, p, o);
	if (cmp(o, t) != 0) return 0;
	a[0] = 3;
	for (int i = 0; i < MAX; ++i) o[i] = 0;
	expmod(a, s, p, o);
	if (cmp(o, t) != 0) return 0;
	a[0] = 5;
	for (int i = 0; i < MAX; ++i) o[i] = 0;
	expmod(a, s, p, o);
	if (cmp(o, t) != 0) return 0;
	a[0] = 7;
	for (int i = 0; i < MAX; ++i) o[i] = 0;
	expmod(a, s, p, o);
	if (cmp(o, t) != 0) return 0;
	return 1;
}
int coprime(int e[MAX], int s[MAX]) {
	int a[MAX], b[MAX], c[MAX], d[MAX], o[MAX], l[MAX];
	for (int i = 0; i < MAX; ++i) l[i] = o[i] = c[i] = d[i] = 0;
	o[0] = 0; o[MAX - 1] = 1;
	l[0] = 1; l[MAX - 1] = 1;
	mov(e, b);
	mov(s, a);
	do {
		if (cmp(b, l) == 0) return 1;
		for (int i = 0; i < MAX; ++i) c[i] = 0;
		divt(a, b, d, c);
		mov(b, a);
		mov(c, b);
	} while (cmp(c, o) != 0);
	return 0;
}
void prime_random(int *p, int *q) {
	p[0] = 1; p[MAX - 1] = 10;
	q[0] = 3; q[MAX - 1] = 11;
	do {
		srand(time(0));
		for (int i = 1; i < p[MAX - 1] - 1; ++i) p[i] = rand() % 10;
		p[p[MAX - 1] - 1] = rand() % 9 + 1;
	} while (is_prime_san(p) != 1);
	do {
		srand(time(0));
		for (int i = 1; i < q[MAX - 1] - 1; ++i) q[i] = rand() % 10;
		q[q[MAX - 1] - 1] = rand() % 9 + 1;
	} while (is_prime_san(q) != 1);
}
void erand(int e[MAX], int m[MAX]) {
	int i, k;
	e[MAX - 1] = 5;
	do {
		srand(time(0));
		for (int i = 0; i < e[MAX - 1] - 1; ++i) e[i] = rand() % 10;
		e[e[MAX - 1] - 1] = rand() % 9 + 1;
	} while (coprime(e, m) != 1);
}
void rsa(int e[MAX], int g[MAX], int *d) {
	int	r[MAX], n1[MAX], n2[MAX], k[MAX], w[MAX];
	int t[MAX], b1[MAX], b2[MAX], temp[MAX];
	mov(g, n1);
	mov(e, n2);
	for (int i = 0; i < MAX; ++i) k[i] = w[i] = r[i] = temp[i] = b1[i] = b2[i] = t[i] = 0;
	b1[0] = 0; b1[MAX - 1] = 0;
	b2[0] = 1; b2[MAX - 1] = 1;
	for (;;) {
		for (int i = 0; i < MAX; ++i) k[i] = w[i] = 0;
		divt(n1, n2, k, w);
		for (int i = 0; i < MAX; ++i) temp[i] = 0;
		mul(k, n2, temp);
		for (int i = 0; i < MAX; ++i) r[i] = 0;
		sub(n1, temp, r);
		if (r[MAX - 1] == 1 && r[0] == 0) break;
		else {
			mov(n2, n1);
			mov(r, n2);
			mov(b2, t);
			for (int i = 0; i < MAX; ++i) temp[i] = 0;
			mul(k, b2, temp);
			for (int i = 0; i < MAX; ++i) b2[i] = 0;
			sub(b1, temp, b2);
			mov(t, b1);
		}
	}
	for (int i = 0; i < MAX; ++i) t[i] = 0;
	add(b2, g, t);
	for (int i = 0; i < MAX; ++i) temp[i] = d[i] = 0;
	divt(t, g, temp, d);
}
struct slink *input(void) {
	struct slink *head, *p1, *p2;
	int i, n = 0, c, temp;
	char ch;
	p1 = p2 = (struct slink *)malloc(LEN);
	head = NULL;
	printf("请输入你所要加密的内容：");
	while ((ch = getchar()) != '\n') {
		i = 0;
		c = ch;
		if (c < 0) {
			c = abs(c);
			p1->bignum[MAX - 2] = '0';
		}
		else {
			p1->bignum[MAX - 2] = '1';
		}
		while(c != 0) {
			p1->bignum[i++] = c % 10;
			c /= 10;
		}
		p1->bignum[MAX - 1] = i;
		++n;
		if (n == 1) head = p1;
		else p2->next = p1;
		p2 = p1;
		p1 = (struct slink *)malloc(LEN);
	}
	p2->next = NULL;
	return head;
}
struct slink *encrypt(int e[MAX], int n[MAX], struct slink *head) {
	struct slink *p, *h, *p1, *p2;
	printf("\n加密后形成的密文内容：\n");
	p1 = p2 = (struct slink*)malloc(LEN);
	h = NULL;
	int m = 0;
	for (p = head; p; p = p->next) {
		expmod(p->bignum , e , n , p1->bignum);
		for (int i = 0; i < p1->bignum[MAX - 1]; ++i)
			printf("%d", p1->bignum[p1->bignum[MAX - 1] - 1 - i]);
		++m;
		if (m == 1) h = p1;
		else p2->next = p1;
		p2 = p1;
		p1 = (struct slink *)malloc(LEN);
	}
	p2->next = NULL;
	printf("\n");
	return h;
}
void decrypt(int d[MAX], int n[MAX], struct slink *h) {
	int	j = 0, temp;
	struct slink *p, *p1;
	char ch[65535];
	p1 = (struct slink*)malloc(LEN);
	for (p = h; p; p = p->next) {
		for (int i = 0; i < MAX; ++i) p1->bignum[i] = 0;
		expmod(p->bignum , d , n , p1->bignum);
		temp = p1->bignum[0] + p1->bignum[1] * 10 + p1->bignum[2] * 100;
		if (p1->bignum[MAX - 2] == '0') temp = -temp;
		ch[j] = temp;
		++j;
	}
	printf("解密密文后所生成的明文:\n");
	for (int i = 0; i < j; ++i) printf("%c", ch[i]);
	printf("\n");
}
int main() {
	int p[MAX], q[MAX], n[MAX], d[MAX], e[MAX], m[MAX], p1[MAX], q1[MAX];
	struct slink *head, *h1, *h2;
	// 扩展欧几里得
	int a_1[MAX], p_1[MAX], n_1[MAX], result_1[MAX];
	a_1[0] = 3; a_1[MAX - 1] = 1;
	p_1[0] = 5; p_1[MAX - 1] = 1;
	n_1[0] = 7; n_1[MAX - 1] = 1;
	expmod(a_1, p_1, n_1, result_1);
	printf("3在模7下的逆元为：");
	print(result_1);
	// Miller-Rabin素性测试
	p[0] = 1; p[MAX - 1] = 10;
	q[0] = 3; q[MAX - 1] = 11;
	srand(time(0));
	for (int i = 1; i < p[MAX - 1] - 1; ++i) p[i] = rand() % 10;
	p[p[MAX - 1] - 1] = rand() % 9 + 1;
	printf("\n随机产生的数为：");
	print(p); 
	printf("它%s一个质数\n", is_prime_san(p) ? "是" : "不是");
	// 计算7^563 mod 561
	memset(a_1, 0, sizeof(a_1));
	memset(p_1, 0, sizeof(p_1));
	memset(n_1, 0, sizeof(n_1));
	a_1[0] = 7; a_1[MAX - 1] = 1;
	p_1[0] = 3; p_1[1] = 6; p_1[2] = 5; p_1[MAX - 1] = 3;
	n_1[0] = 1; n_1[1] = 6; n_1[2] = 5; n_1[MAX - 1] = 3;
	expmod(a_1, p_1, n_1, result_1);
	printf("\n7^563 mod 561 = ");
	print(result_1);
	// 实现RSA算法
	printf("\nRSA所需的密钥对生成中，请稍后……\n"); 
	for (int i = 0; i < MAX; ++i) m[i] = p[i] = q[i] = n[i] = d[i] = e[i] = 0; 
	for (int i = 0; i < MAX; ++i) m[i] = p[i] = q[i] = n[i] = d[i] = e[i] = 0;
	prime_random(p, q);
	mul(p, q, n);
	mov(p, p1);
	--p1[0];
	mov(q, q1);
	--q1[0];
	mul(p1, q1, m);
	erand(e, m);
	rsa(e, m, d);
	head = input();
	h1 = encrypt(e, n, head);
	decrypt(d, n, h1);
	return 0;
}
