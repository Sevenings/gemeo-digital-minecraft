import sqlite3

# Conecta ao banco de dados
conn = sqlite3.connect('mensagens.db')
cursor = conn.cursor()

# Executa uma consulta
cursor.execute('SELECT * FROM mensagens')

# Exibe o resultado
for row in cursor.fetchall():
    print(row)

# Fecha a conexão
conn.close()
