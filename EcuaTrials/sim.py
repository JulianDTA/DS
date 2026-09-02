class Card:
    def __init__(self, name, play_again=False, steal=False, draw=False):
        self.name = name
        self.play_again = play_again
        self.steal = steal
        self.draw = draw

class Deck:
    def __init__(self):
        self.mano = []
        self.mazo = [Card('Atq1'), Card('Atq2'), Card('Atq3'), Card('Atq4'), Card('Atq5')]
    def draw(self, n):
        for _ in range(n):
            if self.mazo and len(self.mano) < 10:
                self.mano.append(self.mazo.pop())
    def play(self, idx):
        return self.mano.pop(idx)

p1 = Deck()
p2 = Deck()

p1.draw(3)
p2.draw(3)

print(f"P1 draws 3. Hand size: {len(p1.mano)}. Cards: {[c.name for c in p1.mano]}")
print(f"P2 draws 3. Hand size: {len(p2.mano)}. Cards: {[c.name for c in p2.mano]}")

print("\n--- TURN 1 ---")
# Player 1 turn
c = p1.play(0)
print(f"P1 plays {c.name}. Hand size becomes {len(p1.mano)}.")

# AI turn
c2 = p2.play(0)
c2.steal = True # Simulate Inocencia Fingida
print(f"AI plays {c2.name} (Steals). AI hand becomes {len(p2.mano)}.")
if c2.steal and len(p1.mano) > 0:
    stolen = p1.mano.pop(0)
    p2.mano.append(stolen)
    print(f"AI steals {stolen.name} from P1! P1 hand becomes {len(p1.mano)}. AI hand becomes {len(p2.mano)}.")

print("\n--- TURN 2 ---")
# Player 1 plays FX_DRAW
c3 = Card("Busca Frenetica", play_again=True, draw=True)
p1.mano.append(c3)
print(f"P1 hand before play: {[c.name for c in p1.mano]}")
played = p1.play(-1)
print(f"P1 plays {played.name}. Hand size drops to {len(p1.mano)}.")
if played.draw:
    p1.draw(1)
    print(f"Card effect DRAW 1. P1 hand size rises to {len(p1.mano)}.")
