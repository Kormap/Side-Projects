def num_atoms(amount_in_grams,atomic_weight=196.97):
    avogadro=6.022*(10e+22)
    print(6.022*(10e+22))
    num_at_atoms=float(amount_in_grams)*avogadro/float(atomic_weight)
    return num_at_atoms
