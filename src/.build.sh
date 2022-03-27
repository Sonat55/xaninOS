#UBUNTU TEST
#add 32-bit gcc cross-compiler to your $PATH variable
#ASSEMBLER COMPILATION
nasm -fbin ./boot/boot.asm 
nasm -fbin ./boot/locateFS.asm
nasm -fbin ./boot/kernelLoader.asm

nasm -fbin ./xin_fs/xin_pointers.asm
nasm -fbin ./xin_fs/entries_table.asm

cd ./handlers
nasm -f elf32 keyboard.asm -o keyboard.o
cd ..

cd ./syscall
nasm -f elf32 syscall.asm -o syscall.o
cd ..

cd ./pit
nasm -f elf32 pit.asm -o pit.o
cd ..

cd ./lib
nasm -f elf32 v86_mode.asm -o v86_mode.o
cd ..

cd ./xin_fs
nasm -f bin xanin_fs_saver.asm -o xanin_fs_saver
cd ..

#COMPILE																										 HERE YOU MUST PUT PATH TO SRC DIRECTORY
i386-elf-gcc -O0 -masm=intel -Wno-builtin-declaration-mismatch -nostdlib -ffreestanding -Wno-int-conversion -Wno-unused-function -I /home/witut/Desktop/xaninOS/src kernel.c ./handlers/keyboard.o ./pit/pit.o ./syscall/syscall.o ./lib/v86_mode.o -o kernel.bin
#dd if=/dev/zero of=zero.img bs=512 count=2024

cat ./boot/boot ./xin_fs/xanin_fs_saver ./xin_fs/xin_pointers ./xin_fs/entries_table ./boot/kernelLoader kernel.bin > xanin.bin

#MOV XANIN.img to BIN
dd if=xanin.bin of=xanin.img
mv xanin.img -f ../bin
rm xanin.bin 
rm kernel.bin
