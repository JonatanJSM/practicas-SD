package pubsub

type Message struct {
	// El tema
	topic string

	// El mensaje
	body string
}

func NewMessage(msg string, topic string) *Message {
	// Crear un nuevo mensaje
	return &Message{
		topic: topic,
		body:  msg,
	}
}

func (m *Message) GetTopic() string {
	// Retornar el tema del mensaje
	return m.topic
}

func (m *Message) GetMessageBody() string {
	// Retornar el cuerpo del mensaje
	return m.body
}
