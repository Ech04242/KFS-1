FROM debian:stable-slim


RUN apt update
RUN apt install grub-pc-bin mtools xorriso -y


WORKDIR /app

CMD ["grub-mkrescue", "-o", "kfs1.iso", "kfs1.bin"]


