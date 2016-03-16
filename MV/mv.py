import sys

def get_data(vaddr, pdbr, mem, disk):
    print('Virtual Address %04x:' % vaddr)
    pde_index = vaddr >> 10
    ped = mem[pdbr + pde_index]
    valid_bit = ped >> 7
    pfn = ped & 0b01111111
    pt = pfn << 5
    print('  --> pde index:0x%x  pde contents:(valid %i, pfn 0x%x)' % (pde_index, valid_bit, pfn))

    dev = mem if valid_bit == 1 else disk
    if dev == disk and pfn == 0x7F:
        print('    --> Data missing')
        return

    pte_index = (vaddr >> 5) & 0b11111
    pte = dev[pt + pte_index]
    valid_bit = pte >> 7
    pfn = pte & 0b01111111
    print('    --> pte index:0x%x  pte contents:(valid %i, pfn 0x%x)' % (pte_index, valid_bit, pfn))

    dev = mem if valid_bit == 1 else disk
    if dev == disk and pfn == 0x7F:
        return None

    paddr = (pfn << 5) + (vaddr & 0b11111)
    if valid_bit == 1:
        print('      --> To Physical Address 0x%x --> Value: %02x' % (paddr, mem[paddr]))
    elif pfn != 0x7F:
        print('      --> To Disk Sector Address 0x%x --> Value: %02x' % (paddr, disk[paddr]))
    else:
        print('      --> Data missing')

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
    disk = load_data('disk.txt')
    pdbr = 0xd80
    get_data(vaddr, pdbr, memory, disk)
