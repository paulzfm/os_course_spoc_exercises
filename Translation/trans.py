
def trans(pdbr, va, pa):
    pde_idx = va >> 20
    pte_idx = (va >> 12) & 0xFF
    pt = pa >> 12
    pte_cxt = (pt << 12) & 0b000000000011
    pt = pde_idx - 0x300 + 1
    pde_cxt = (pt << 12) & 0b000000000011
    print 'va 0x%08x, pa 0x%08x, pde_idx 0x%08x, pde_ctx 0x%08x, pte_idx 0x%08x, pte_ctx 0x%08x' % (va, pa, pde_idx, pde_cxt, pte_idx, pte_cxt)

trans(0, 0xcd82c07c, 0x0c20907c)
