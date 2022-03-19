
#define DMA_SLAVE 0x0
#define DMA_MASTER 0x1

enum dma_slave_ports
{
    DMA_SLAVE_STATUS_REGISTER = 0x8,
    DMA_SLAVE_COMMAND_REGISTER = 0x8,
    
    DMA_SLAVE_REQUEST_REGISTER = 0x9,
    DMA_SLAVE_CHANGE_MASK_REGISTER = 0xA,
    
    DMA_SLAVE_MODE_REGISTER = 0xB,
    DMA_SLAVE_CLEAR_FLIP_FLOP = 0xC,    
    
    DMA_SLAVE_INTERMEDIATE_REGISTER = 0xD,
    DMA_SLAVE_MASTER_CLEAR_REGISTER = 0xD,
    
    DMA_SLAVE_CLEAR_MASK_REGISTER = 0xE,
    DMA_SLAVE_WRITE_MASK_REGISTER = 0xF,

};

enum dma_slave_channel_ports
{
    DMA_SLAVE_CHAN0_ADDRESS_REG = 0x0,
    DMA_SLAVE_CHAN0_COUNT_REG = 0x1,

    DMA_SLAVE_CHAN1_ADDRESS_REG = 0x2,
    DMA_SLAVE_CHAN1_COUNT_REG = 0x3,

    DMA_SLAVE_CHAN2_ADDRESS_REG = 0x4,
    DMA_SLAVE_CHAN2_COUNT_REG = 0x5,

    DMA_SLAVE_CHAN3_ADDRESS_REG = 0x6,
    DMA_SLAVE_CHAN3_COUNT_REG = 0x7,
};

enum dma_master_ports
{
    MASTER_STATUS_REGISTER = 0xD0,
    MASTER_COMMAND_REGISTER = 0xD0,

    DMA_MASTER_REQUEST_REGISTER = 0xD2,
    DMA_MASTER_CHANGE_MASK_REGISTER = 0xD4,

    DMA_MASTER_MODE_REGISTER = 0xD6,
    DMA_MASTER_CLEAR_FLIP_FLOP = 0xD8,

    DMA_MASTER_INTERMEDIATE_REGISTER = 0xDA,
    DMA_MASTER_CLEAR_MASTER = 0xDA,

    DMA_MASTER_CLEAR_MASK_REGISTER = 0xDC,
    DMA_MASTER_WRITE_MASK_REGISTER = 0xDE
};

enum dma_master_channel_ports
{
    DMA_MASTER_CHAN4_ADDRESS_REG = 0xC0,    /* unusable */
    DMA_MASTER_CHAN4_COUNT_REG = 0xC2,      /* unusable */

    DMA_MASTER_CHAN5_ADDRESS_REG = 0xC4,
    DMA_MASTER_CHAN5_COUNT_REG = 0xC6,

    DMA_MASTER_CHAN6_ADDRESS_REG = 0xC8,
    DMA_MASTER_CHAN6_COUNT_REG = 0xCA,

    DMA_MASTER_CHAN7_ADDRESS_REG = 0xCC,
    DMA_MASTER_CHAN7_COUNT_REG = 0xCE,
};

enum dma_commands 
{

	DMA_CMD_MASK_MEMTOMEM = 0x1,
	DMA_CMD_MASK_CHANNEL_0_ADDRESS_HOLD = 0x2,
	
    DMA_CMD_MASK_ENABLE = 0x4,
	DMA_CMD_MASK_TIMING = 0x8,
	
    DMA_CMD_MASK_PRIORITY = 0x10,
	DMA_CMD_MASK_WRITESEL = 0x20,
	
    DMA_CMD_MASK_DREQ = 0x40,
	DMA_CMD_MASK_DACK = 0x80
};

enum dma_modes
{

	DMA_MODE_MASK_SEL = 0x3,
	DMA_MODE_MASK_TRA = 0xC,

	DMA_MODE_SELF_TEST = 0x0,
	DMA_MODE_READ_TRANSFER = 0x4,
	
    DMA_MODE_WRITE_TRANSFER = 0x8,
	DMA_MODE_MASK_AUTO = 0x10,
	
    DMA_MODE_MASK_IDEC = 0x20,
	DMA_MODE_MASK = 0xC0,
	
    DMA_MODE_TRANSFER_ON_DEMAND= 0,
	DMA_MODE_TRANSFER_SINGLE = 0x40,
	
    DMA_MODE_TRANSFER_BLOCK = 0x80,
	DMA_MODE_TRANSFER_CASCADE = 0xC0
};