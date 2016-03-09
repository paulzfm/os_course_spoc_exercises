import sys

# addr -> addr -> [byte] -> addr option
def virtual2physical(vaddr, pdbr, mem):
    ped_index = vaddr >> 10
    # print(hex(ped_index))
    ped = mem[pdbr + ped_index]
    valid_bit = ped & 0b10000000
    if not valid_bit:
        return None
    pt = (ped & 0b01111111) << 5
    # print(bin(ped & 0b01111111))
    pte_index = (vaddr >> 5) & 0b11111
    # print(hex(pte_index))
    pte = mem[pt + pte_index]
    valid_bit = pte & 0b10000000
    if not valid_bit:
        return None
    pfn = pte & 0b01111111
    # print(bin(pfn))
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
    if len(sys.argv) != 2:
        print('Usage: python %s <vaddr in hex>' % sys.argv[0])
        sys.exit(1)

    vaddr = int(sys.argv[1], 16)
    memory = load_data('memory.txt')
    pdbr = 0x220
    paddr = virtual2physical(vaddr, pdbr, memory)
    if not paddr:
        print('page fault')
    else:
        print('paddr: %s' % hex(paddr))
        print('value: %s' % hex(memory[paddr]))
