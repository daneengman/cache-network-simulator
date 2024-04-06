PIC_LD=ld

ARCHIVE_OBJS=
ARCHIVE_OBJS += _prev_archive_1.so
_prev_archive_1.so : archive.4/_prev_archive_1.a
	@$(AR) -s $<
	@$(PIC_LD) -shared  -o .//../dpi_shared.so.daidir//_prev_archive_1.so --whole-archive $< --no-whole-archive
	@rm -f $@
	@ln -sf .//../dpi_shared.so.daidir//_prev_archive_1.so $@






%.o: %.c
	$(CC_CG) $(CFLAGS_CG) -c -o $@ $<
CU_UDP_OBJS = \


CU_LVL_OBJS = \
SIM_l.o 

MAIN_OBJS = \
amcQwB.o objs/amcQw_d.o 

CU_OBJS = $(MAIN_OBJS) $(ARCHIVE_OBJS) $(CU_UDP_OBJS) $(CU_LVL_OBJS)
