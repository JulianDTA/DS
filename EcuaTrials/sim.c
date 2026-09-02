#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_HAND_SIZE 10
#define MAX_DECK_SIZE 40

typedef struct {
    int id;
    const char* nombre;
    int efectos;
    int ataque;
    int escudo;
    int curacion;
    int robar;
} CardData;

typedef struct {
    const CardData* mazo[MAX_DECK_SIZE];
    int mazo_top;
    const CardData* mano[MAX_HAND_SIZE];
    int mano_size;
    const CardData* descarte[MAX_DECK_SIZE];
    int descarte_size;
} DeckState;

#define FX_ATTACK       (1 << 0)
#define FX_PLAY_AGAIN   (1 << 4)
#define FX_STEAL_HAND   (1 << 5)

bool deck_draw(DeckState* ds, int n) {
    for (int i=0; i<n; i++) {
        if (ds->mano_size >= MAX_HAND_SIZE) return false;
        if (ds->mazo_top <= 0) return false;
        ds->mazo_top--;
        ds->mano[ds->mano_size++] = ds->mazo[ds->mazo_top];
    }
    return true;
}

const CardData* deck_play_from_hand(DeckState* ds, int index) {
    if (index < 0 || index >= ds->mano_size) return NULL;
    const CardData* c = ds->mano[index];
    ds->descarte[ds->descarte_size++] = c;
    for(int i=index; i<ds->mano_size-1; i++) ds->mano[i] = ds->mano[i+1];
    ds->mano_size--;
    return c;
}

int main() {
    CardData c1 = {1, "Ataque", FX_ATTACK, 3, 0, 0, 0};
    CardData c2 = {2, "Combo", FX_ATTACK | FX_PLAY_AGAIN, 1, 0, 0, 0};
    CardData c3 = {3, "Robar", FX_STEAL_HAND, 0, 0, 0, 0};

    DeckState p1 = {0};
    DeckState p2 = {0};

    p1.mazo[0] = &c1; p1.mazo[1] = &c2; p1.mazo[2] = &c3; p1.mazo_top = 3;
    p2.mazo[0] = &c1; p2.mazo[1] = &c1; p2.mazo_top = 2;

    deck_draw(&p1, 2); // draws c3, c2
    deck_draw(&p2, 1); // draws c1

    printf("P1 Mano: %d, P2 Mano: %d\n", p1.mano_size, p2.mano_size);
    printf("P1 Juega Combo\n");
    deck_play_from_hand(&p1, 1); // c2
    
    // ... simulate FX_PLAY_AGAIN
    printf("P1 Juega Robar\n");
    const CardData* p_c = deck_play_from_hand(&p1, 0); // c3
    if (p_c->efectos & FX_STEAL_HAND) {
        printf("P1 roba de P2\n");
        const CardData* st = p2.mano[0];
        p2.mano_size--;
        p1.mano[p1.mano_size++] = st;
    }
    printf("P1 Mano: %d, P2 Mano: %d\n", p1.mano_size, p2.mano_size);
    return 0;
}
