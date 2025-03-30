Implementação de um codificador de decodificador de Cifras de Beale.
  
Utilização:

Codificar uma mensagem qualquer contida em um arquivo ASCII usando um livro cifra. O programa deve ter uma opção de salvar em um arquivo texto as chaves geradas no formato descrito anteriormente. A linha de execução do programa dever ser a seguinte:

./beale  -e  -b LivroCifra -m MensagemOriginal -o MensagemCodificada -c ArquivoDeChaves 

Decodificar uma mensagem, usando um arquivo de códigos:

./beale  -d  -i MensagemCodificada  -c ArquivoDeChaves  -o MensagemDecodificada 

Decodificar uma mensagem usando o livro cifra:

./beale -d -i MensagemCodificada -b LivroCifra -o MensagemDecodificada 
