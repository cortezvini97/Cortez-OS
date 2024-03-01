# -*- coding: utf-8 -*-


param(
    [string]$Action
)

# Define a função para compilar e linkar o código
function Compile {
    docker run --rm -it -v "${pwd}:/root/env" cortezos
}

# Define a função para executar o kernel, se existir
function Run-Kernel {
    if (Test-Path "dist/kernel.bin") {
        qemu-system-x86_64 -kernel dist/kernel.bin
    } else {
        "O arquivo kernel.bin não foi encontrado. Não é possível executar o comando."
    }
}

function Run-Kernel-Iso {
    if (Test-Path "dist/cortezos.iso") {
        qemu-system-x86_64 -cdrom dist/cortezos.iso
    } else {
        "O arquivo cortezos.iso não foi encontrado. Não é possível executar o comando."
    }
    
}

# Verifica o argumento passado e executa as funções apropriadas
if ($Action -eq "--all") {
    Compile
    Run-Kernel-iso
} elseif ($Action -eq "--compile") {
    Compile
} elseif ($Action -eq "--runkernelmode") {
    Run-Kernel
} elseif ($Action -eq "--runkerneliso"){
    Run-Kernel-Iso
} else {
    Write-Output "Uso: ./build.ps1 --all | --compile | --runkernelmode | --runkerneliso"
}