import sqlite3


def init_db():
    """Cria o banco de dados se não existir."""
    conn = sqlite3.connect("mensagens.db")
    cursor = conn.cursor()
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS mensagens (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            topico TEXT NOT NULL,
            mensagem TEXT NOT NULL,
            timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
        )
    """)
    conn.commit()
    conn.close()


def salvar_mensagem(topico, mensagem):
    """Salva uma mensagem no banco de dados."""
    conn = sqlite3.connect("mensagens.db")
    cursor = conn.cursor()
    cursor.execute(
        "INSERT INTO mensagens (topico, mensagem) VALUES (?, ?)", (topico, mensagem))
    conn.commit()
    conn.close()


def obter_mensagens():
    """Retorna as últimas 10 mensagens do banco."""
    conn = sqlite3.connect("mensagens.db")
    cursor = conn.cursor()
    cursor.execute(
        "SELECT topico, mensagem FROM mensagens ORDER BY timestamp DESC LIMIT 10")
    mensagens = cursor.fetchall()
    conn.close()
    return mensagens


init_db()  # Garantir que o BD seja criado ao iniciar
