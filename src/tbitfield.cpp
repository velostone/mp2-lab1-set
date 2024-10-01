// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <string>

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len) : BitLen(len)
{
    if (len > 0) {
        if (BitLen % (8 * sizeof(TELEM)) == 0)
            MemLen = BitLen / (8 * sizeof(TELEM));
        else MemLen = BitLen / (8 * sizeof(TELEM)) + 1;
        pMem = new TELEM[MemLen]{ 0 };
    }
  // else throw length_error("Incorrect lenght!");
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
    delete[] pMem;
    pMem = nullptr;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return (n / (8 * sizeof(TELEM)));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    int shift = n % (8 * sizeof(TELEM));
    return (1<<shift);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n > -1 && n < BitLen) {
        int val = GetMemIndex(n);
        pMem[val] = pMem[val] | GetMemMask(n);
    }
   else throw range_error("Out of range!");
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n > -1 && n < BitLen) {
        int val = GetMemIndex(n);
        pMem[val] = pMem[val] & ~GetMemMask(n);
    }
   else throw range_error("Out of range!");
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n > -1 && n < BitLen) {
        int index = GetMemIndex(n);
        if ((pMem[index] & GetMemMask(n)) == 0)
            return 0;
        else return 1;
    }
   else throw range_error("Out of range!");
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this != &bf) {
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++)
            pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen == bf.BitLen) {
        for (int i = 0; i < MemLen; i++)
            if (pMem[i] != pMem[i])
            {
                return 0;
            };
        return 1;
    }
    else return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (BitLen == bf.BitLen) {
        for (int i = 0; i < MemLen; i++)
            if (pMem[i] != bf.pMem[i])
            {
                return 1;
            };
        return 0;
    }
    else return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    TBitField A(max(BitLen, bf.BitLen));
    for (int i = 0; i < min(MemLen, bf.MemLen); i++)
        A.pMem[i] = pMem[i] | bf.pMem[i];
    return A;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    TBitField A(max(BitLen, bf.BitLen));
    for (int i = 0; i < min(MemLen, bf.MemLen); i++)
        A.pMem[i] = pMem[i] & bf.pMem[i];
    return A;
}

TBitField TBitField::operator~(void) // отрицание
{
    for (int i = 0; i < MemLen; i++)
        pMem[i] = ~pMem[i];
    pMem[MemLen - 1] = pMem[MemLen - 1] & (GetMemMask(8 * MemLen - BitLen) - 1);
    return *this;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    string cin;
    istr >> cin;
    if (cin.size() <= bf.BitLen)
        for (int i = 0; i < cin.size(); i++) {
            if (cin[i] == '1') bf.SetBit(i);
            else if (cin[i] == '0') bf.ClrBit(i);
            else throw invalid_argument("A symbol must be 0 or 1!");
        }
    else throw length_error("Incorrect length!");
    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++)
        ostr << bf.GetBit(i);
    return ostr;
}