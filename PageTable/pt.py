
# addr -> addr -> [byte] -> addr option
def virtual2physical(vaddr, pdbr, mem):
    ped_index = vaddr >> 10
    ped = mem[pdbr + ped_index]
    valid_bit = ped & 0b10000000
    if not valid_bit:
        return None
    pt = (ped & 0b01111111) << 5
    pte_index = (vaddr >> 5) & 0b11111
    pte = mem[pt + pte_index]
    valid_bit = pte & 0b10000000
    if not valid_bit:
        return None
    pfn = pte & 0b01111111
    return (pfn << 5) + (vaddr & 0b11111)

def load_data(file_path):
    mem = []
    with open(file_path, 'r') as f:
        for line in f.readlines():
            line = line.replace('\n', '')
            bs = (line.split(':')[1]).split(' ')[1:]
            for byte in bs:
                mem.append(int(byte, 16))

    return mem

if __name__ == '__main__':
    memory = load_data('memory.txt')
    pdbr = 0x220
    paddr = virtual2physical(0x3df, pdbr, memory)
    print('addr: %s' % hex(paddr))
    print('value: %s' % hex(memory[paddr]))
