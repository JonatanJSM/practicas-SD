package pubsub

import (
	"crypto/rand"
	"fmt"
	"log"
	"sync"
)

type Subscriber struct {
	id       string          // ID del usuario
	messages chan *Message   // Canal del mensaje
	topics   map[string]bool // Temas a los que está suscrito el usuario
	active   bool            // Si el usuario está activo o no
	mutex    sync.RWMutex    // Para bloquear al susbcriber solo para read y write
}

func CreateNewSubscriber() (string, *Subscriber) { // Retorna un nuevo suscriptor
	b := make([]byte, 8)   // Crea un canal que será un arreglo de 8 bytes
	_, err := rand.Read(b) // Llena el arreglo con números aleatorios
	if err != nil {        // Verifica que no haya error durante generación de num aleatorios
		log.Fatal(err)
	}
	id := fmt.Sprintf("%X-%X", b[0:4], b[4:8]) // ID hexadecimal
	return id, &Subscriber{
		id:       id,
		messages: make(chan *Message),
		topics:   map[string]bool{},
		active:   true,
	}
}

func (s *Subscriber) AddTopic(topic string) { //Agrega un tema a la lista del suscriptor
	s.mutex.RLock()
	defer s.mutex.RUnlock()
	s.topics[topic] = true
}

func (s *Subscriber) RemoveTopic(topic string) { //Remueve un tema de la lista del suscriptor
	s.mutex.RLock()
	defer s.mutex.RUnlock()
	delete(s.topics, topic)
}

func (s *Subscriber) GetTopics() []string { //Devuelve la lista de temas del suscriptor
	s.mutex.RLock()
	defer s.mutex.RUnlock()
	topics := []string{}
	for topic, _ := range s.topics { //Utilizamos solo el nombre del tema
		topics = append(topics, topic)
	}
	return topics
}

func (s *Subscriber) Destruct() { //Desactiva al suscriptor
	s.mutex.RLock()
	defer s.mutex.RUnlock()
	s.active = false
	close(s.messages) //Cierra el canal
}

func (s *Subscriber) Signal(msg *Message) { //Envía el mensaje del canal al suscriptor si está activo
	s.mutex.RLock()
	defer s.mutex.RUnlock()
	if s.active {
		s.messages <- msg
	}
}

func (s *Subscriber) Listen() { //Imprime el mensaje cuando ya se recibió
	for {
		if msg, ok := <-s.messages; ok {
			fmt.Printf("Suscriptor %s, recibe el mensaje: %s del topic: %s\n", s.id, msg.GetMessageBody(), msg.GetTopic())
		}
	}
}
