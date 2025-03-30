# Nome do arquivo de entrada
input_file="output.txt"

# Lê o arquivo de entrada e processa cada instância
instance_number=1
while IFS= read -r line
do
    if [[ $line == Instance* ]]; then
        # Quando uma nova instância começa, cria um arquivo temporário para ela
        instance_file="instance_${instance_number}.txt"
        > "$instance_file"
        ((instance_number++))
    else
        # Escreve a linha no arquivo da instância atual
        echo "$line" >> "$instance_file"
    fi
done < "$input_file"

# Executa o programa para cada arquivo de instância e salva a saída
for ((i = 1; i < instance_number; i++)); do
    ./bin/tp3.out < "instance_${i}.txt" > "output_atualizacao_${i}.txt"
done

# Limpa os arquivos temporários
rm instance_*.txt