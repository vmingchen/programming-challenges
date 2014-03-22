/*
 * ===========================================================================
 *
 *       Filename:  pokerhand.cpp
 *
 *    Description:  PC/UVa, 110202/10315
 *
 *        Version:  1.0
 *        Created:  07/03/2011 03:43:53 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ming Chen (chenming), brianchenming@gmail.com
 *        Company:  imeresearch@sogou
 *
 * ===========================================================================
 */

#include	<stdlib.h>
#include	<stdio.h>
#include	<algorithm>

//#define DEBUG

const int N = 5;

enum HandType {
    HIGH_CARD = 0,
    PAIR,
    TWO_PAIR,
    THREE_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_KIND,
    STRAIGHT_FLUSH
};

class PokerHand {
public:
    virtual ~PokerHand() = 0;
    virtual int GetType() const = 0;
    virtual int GetDataSize() const = 0;
    virtual const int *GetData() const = 0;
};
PokerHand::~PokerHand() {}

int compareHand(const PokerHand *ph1, const PokerHand *ph2) { 
    if (ph1->GetType() != ph2->GetType()) {
        return ph1->GetType() < ph2->GetType() ? -1 : 1;
    }
    int size = ph1->GetDataSize();
    const int *pData1 = ph1->GetData(), 
        *pData2 = ph2->GetData();
    for (int i=0; i < size; ++i) 
        if (pData1[i] != pData2[i]) 
            return pData1[i] < pData2[i] ? -1 : 1;
    return 0;
};

class Card {
public:
    int value, suit;
    Card() : value(0), suit(0) {} 
    int GetValue() const { 
        switch(value) {
            case 'T':
                return 10;
            case 'J':
                return 11;
            case 'Q':
                return 12;
            case 'K':
                return 13;
            case 'A':
                return 14;
            default:
                return (value - '0');
        }
    };
};

bool compareCard(const Card &card1, const Card &card2) { 
    return card1.GetValue() > card2.GetValue();
}

class HighCard : public PokerHand {
public:
    int values[N];
    HighCard(const Card *cards) {
        for (int i=0; i < N; ++i) {
            values[i] = cards[i].GetValue();
        }
    };
    int GetType() const { return HIGH_CARD; };
    int GetDataSize() const { return N; };
    const int* GetData() const { return values; };
};

class Pair : public PokerHand {
public:
    int values[N-1];    // 1 + N-2
    Pair(const Card *cards, int pIndex) {
        int pv = cards[pIndex].GetValue();
        values[0] = pv;
        int j = 1;
        for (int i=0; i < N; ++i) {
            int v = cards[i].GetValue();
            if (v == pv) continue;
            values[j++] = v;
        }
    };
    int GetType() const { return PAIR; };
    int GetDataSize() const { return N-1; };
    const int* GetData() const { return values; };
};

class TwoPair : public PokerHand {
public:
    int values[N-2]; // 1+1+N-4 large pair, small pair, and the rest
    TwoPair(const Card *cards, int largeIndex, int smallIndex) {
        int lpv = cards[largeIndex].GetValue();
        int spv = cards[smallIndex].GetValue();
        values[0] = lpv;
        values[1] = spv;
        for (int i=0; i < N; ++i) {
            int v = cards[i].GetValue();
            if (v == lpv || v == spv) continue;
            values[2] = v;
        }
    }
    int GetType() const { return TWO_PAIR; };
    int GetDataSize() const { return N-2; };
    const int* GetData() const { return values; };
};

class ThreeKind : public PokerHand {
public:
    int values[1]; 
    ThreeKind(const Card *cards, int tkIndex) {
        values[0] = cards[tkIndex].GetValue();
    };
    int GetType() const { return THREE_KIND; };
    int GetDataSize() const { return 1; };
    const int* GetData() const { return values; };
};

class Straight : public PokerHand {
public:
    int values[1];
    Straight(const Card *cards, int stIndex) {
        values[0] = cards[stIndex].GetValue();
    };
    int GetType() const { return STRAIGHT; };
    int GetDataSize() const { return 1; };
    const int* GetData() const { return values; };
};

class Flush : public PokerHand {
public:
    int values[N];
    Flush(const Card *cards) {
        for (int i=0; i < N; ++i) {
            values[i] = cards[i].GetValue();
        }
    };
    int GetType() const { return FLUSH; };
    int GetDataSize() const { return N; };
    const int* GetData() const { return values; };
};

class FullHouse : public PokerHand {
public:
    int values[1];
    FullHouse(const Card *cards, int fhIndex) {
        values[0] = cards[fhIndex].GetValue();
    };
    int GetType() const { return FULL_HOUSE; };
    int GetDataSize() const { return 1; };
    const int* GetData() const { return values; };
};

class FourKind : public PokerHand {
public:
    int values[1];
    FourKind(const Card* cards, int fkIndex) {
        values[0] = cards[fkIndex].GetValue();
    };
    int GetType() const { return FOUR_KIND; };
    int GetDataSize() const { return 1; };
    const int* GetData() const { return values; };
};

class StraightFlush : public PokerHand {
public:
    int values[1];
    StraightFlush(const Card* cards, int sfIndex) {
        values[0] = cards[sfIndex].GetValue();
    };
    int GetType() const { return STRAIGHT_FLUSH; };
    int GetDataSize() const { return 1; };
    const int* GetData() const { return values; };
};

PokerHand* parseHand(Card *cards) {
    std::sort(cards, cards+N, compareCard);
    bool flush = true;
    int fourIndex = -1;
    int threeIndex = -1;
    int pairIndex[2], pairCount = 0;
    int sameCount = 1;
    bool straight = true;
    for (int i=1; i < N; ++i) {
        int cv = cards[i].GetValue();
        int pv = cards[i-1].GetValue();
        if ( cv == pv ) {
            ++sameCount;
        } else {
            if ( sameCount == 4 ) fourIndex = i-1;
            else if ( sameCount == 3 ) threeIndex = i-1;
            else if ( sameCount == 2 ) pairIndex[pairCount++] = i-1;
            sameCount = 1;
        }
        flush = flush && (cards[i].suit == cards[i-1].suit);
        straight = straight && (cv == pv-1);
    }
    if ( sameCount == 4 ) fourIndex = N-1;
    else if ( sameCount == 3 ) threeIndex = N-1;
    else if ( sameCount == 2 ) pairIndex[pairCount++] = N-1;

    if (straight && flush) return new StraightFlush(cards, 0);
    if (fourIndex != -1) return new FourKind(cards, fourIndex);
    if (threeIndex != -1 && pairCount == 1) 
        return new FullHouse(cards, threeIndex);
    if (flush) return new Flush(cards);
    if (straight) return new Straight(cards, 0);
    if (threeIndex != -1) return new ThreeKind(cards, threeIndex);
    if (pairCount == 2) return new TwoPair(cards, pairIndex[0], pairIndex[1]);
    if (pairCount == 1) return new Pair(cards, pairIndex[0]);
    return new HighCard(cards);
}

/* 
 * ===  FUNCTION  ============================================================
 *         Name:  main
 *  Description:  
 * ===========================================================================
 */
    int
main ( int argc, char *argv[] )
{ 
    Card blackCards[N], whiteCards[N];
    char line[6*N+2];
    while (fgets(line, 6*N+1, stdin) != NULL) { 
        for (int i=0; i < N; ++i) {
            blackCards[i].value = line[3*i];
            blackCards[i].suit = line[3*i+1];
        }
        for (int i=0; i < N; ++i) {
            whiteCards[i].value = line[3*N+3*i];
            whiteCards[i].suit = line[3*N+3*i+1];
        }
        PokerHand *pBlackHand = parseHand(blackCards);
        PokerHand *pWhiteHand = parseHand(whiteCards);

#ifdef DEBUG
        {
        printf("black: %d\n", pBlackHand->GetType());
        const int *data = pBlackHand->GetData();
        for (int i=0; i < pBlackHand->GetDataSize(); ++i) {
            printf("\t%d", data[i]);
        }
        printf("\n");
        printf("white: %d\n", pWhiteHand->GetType());
        data = pWhiteHand->GetData();
        for (int i=0; i < pWhiteHand->GetDataSize(); ++i) {
            printf("\t%d", data[i]);
        }
        printf("\n");
        }
#endif

        int cmp = compareHand(pBlackHand, pWhiteHand);
        if (cmp == -1) {
            printf("White wins.\n");
        } else if (cmp == 1) {
            printf("Black wins.\n");
        } else {
            printf("Tie.\n");
        }
        delete pBlackHand;
        delete pWhiteHand;
    }

    return EXIT_SUCCESS;
}			/* ----------  end of function main  ---------- */
