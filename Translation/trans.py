def trans(va, pa):
    pde_idx = va >> 22
    pte_idx = (va >> 12) & 0b1111111111
    pt = pa >> 12
    pte_cxt = (pt << 12) & 0b000000000011
    pde_cxt = (pde_idx - 0x300 + 1) << 12 | 0x03
    #pde_cxt = (pt << 12) & 0b000000000011
    print 'va 0x%08x, pa 0x%08x, pde_idx 0x%08x, pde_ctx 0x%08x, pte_idx 0x%08x, pte_ctx 0x%08x' % (va, pa, pde_idx, pde_cxt, pte_idx, pte_cxt)

if __name__ == '__main__':
    trans(0xc2265b1f, 0x0d8f1b1f)
    trans(0xcc386bbc, 0x0414cbbc)
    trans(0xc7ed4d57, 0x07311d57)
    trans(0xca6cecc0, 0x0c9e9cc0)
    trans(0xc18072e8, 0x007412e8)
    trans(0xcd5f4b3a, 0x06ec9b3a)
    trans(0xcc324c99, 0x0008ac99)
    trans(0xc7204e52, 0x0b8b6e52)
    trans(0xc3a90293, 0x0f1fd293)
    trans(0xce6c3f32, 0x007d4f32)