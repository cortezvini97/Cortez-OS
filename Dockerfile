FROM vinicortez/asm_c_developer:latest

COPY . /root/env
WORKDIR /root/env

CMD ["make"]