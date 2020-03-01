//
// Created by Anxin Guo on 2/20/20.
//

#ifndef MYLIB_BIGINT_H
#define MYLIB_BIGINT_H

constexpr int BIGLEN = 100;

#include <iostream>

class bigint {
private:
    unsigned char v[BIGLEN]{};
    int len{};
public:

//set bigint to 0 with length 1.
void set0() {
    len = 1;
    for (unsigned char & i : v)
        i = 0;
}

//initialize with 0 with length 1
bigint () {
    set0();
}

//initialize with given number <= size of long long
bigint (long long x) {
    int i = 0;
    while (x > 0) {
        v[i++] = x % 10;
        x /= 10;
    }
    len = i;
}

//I/O
void scan() {
    set0();

    char s[BIGLEN];
    scanf("%s", s);
    len = strlen(s);

    for (int i = 0; i < len; i++)
        v[len - 1 - i] = s[i] - '0';
}

void print() const {
    for (int i = len - 1; i >= 0; i--)
        printf("%d", v[i]);
    printf("\n");
}

bigint operator+(const bigint &x) {
    bigint ans;
    ans.len = std::max(len, x.len);

    for (int i = 0; i < ans.len; i++) {
        ans.v[i] += v[i] + x.v[i];
        if (ans.v[i] > 9) {
            ans.v[i+1] ++;
            ans.v[i] -= 10;
        }
    }

    if (ans.v[ans.len])
        ans.len++;
    return ans;
}

//helper: multiplies a bigint with a natural number not bigger than 28.
bigint multiply(int x) const {
    bigint ans;
    if (x == 0)
        return ans;

    ans.len = len;
    for (int i = 0; i < len || ans.v[i]; i++) {
        ans.v[i] += v[i] * x;
        if (ans.v[i] > 9) {
            ans.v[i+1] += ans.v[i] / 10;
            ans.v[i] %= 10;
        }
    }

    while (ans.v[ans.len])
        ans.len++;
    return ans;
}

bigint operator*(const bigint &x) const {
    bigint ans;

    for (int i = x.len - 1; i >= 0; i--) {
        ans.lshift(1);
        ans += (this->multiply(x.v[i]));
    }

    return ans;
}

//ONLY SUBTRACT SMALLER NUMBERS!
bigint operator-(const bigint &x) const {
    bigint ans;
    ans.len = len;

    for (int i = 0; i < len; i++) {
        ans.v[i] += v[i] - x.v[i];
        if (ans.v[i] < 0) {
            ans.v[i] += 10;
            ans.v[i+1]--;
        }
    }

    while (ans.len > 1 && !ans.v[ans.len-1])
        ans.len--;

    return ans;
}

bigint operator%(const bigint &x) const {
    bigint ans = *this;
    ans %= x;
    return ans;
}


//compare two bigints with usual symbols
bool operator==(const bigint &x) const {
    if(len != x.len)
        return false;

    for (int i = 0; i <= len; i++)
        if (v[i] != x.v[i])
            return false;

    return true;
}

bool operator<(const bigint &x) const {
    if (len != x.len)
        return len < x.len;
    for (int i = len - 1; i >= 0; i--) {
        if (v[i] != x.v[i])
            return v[i] < x.v[i];
    }
    return false;
}

bool operator>(const bigint &x) const {
    if (*this == x)
        return false;
    return !(*this < x);
}

//shorthands for modifying object;
void lshift(int n) {
    for (int i = len - 1; i >= 0; i--)
        v[i+n] = v[i];
    for (int i = 0; i < n; i++)
        v[i] = 0;
    len += n;
}

void rshift(int n) {
    len -= n;
    for (int i = 0; i < len; i++)
        v[i] = v[i+n];
    for (int i = 0; i < n; i++)
        v[i+len] = 0;
}

void operator+=(const bigint &x) {
    *this = *this + x;
}

void operator*=(const bigint &x) {
    *this = *this * x;
}

void operator-=(const bigint &x) {
    *this = *this - x;
}

void operator%=(const bigint &x) {
    if (*this < x)
        return;

    int dif = len - x.len;
    while (dif >= 0) {
        bigint temp = x;
        temp.lshift(dif);
        int n = 9;

        while (temp.multiply(n) > *this)
            n--;

        *this -= temp.multiply(n);
        dif--;
    }
}

/*  void operator/=(const bigint &x) {
    *this = *this / x;
  }*/
};


/*bigint euHelp(bigint &x, bigint &y) {
    x %= y;
    //x.print();
    if (x == ZERO)
        return y;
    return euHelp(y, x);
}

bigint euclid(const bigint &x, const bigint &y) {
    bigint x1 = x, y1 = y;
    return euHelp(x1, y1);
}*/



#endif //MYLIB_BIGINT_H
