package pubsub

import (
	"fmt"
	"sync"
)

type Subscribers map[string]*Subscriber // Crea un nuevo tipo que es un mapa de suscriptores

type Broker struct {
	subscribers Subscribers            // Mapa de suscriptores
	topics      map[string]Subscribers // Mapa de temas/topic
	mut         sync.RWMutex           // Bloquea al broker solo para read y write
}

func NewBroker() *Broker { // Crea una instancia de broker
	return &Broker{
		subscribers: Subscribers{},
		topics:      map[string]Subscribers{},
	}
}

// (b * Broker) Para que el struc pueda usar esta función como método  broker.AddSubscriber()
func (b *Broker) AddSubscriber() *Subscriber { //Añade un suscriptor al broker
	b.mut.Lock()
	defer b.mut.Unlock()
	id, s := CreateNewSubscriber()
	b.subscribers[id] = s
	return s
}

func (b *Broker) Subscribe(s *Subscriber, topic string) { //Suscribe un broker a un tema/topic
	b.mut.Lock()
	defer b.mut.Unlock()

	if b.topics[topic] == nil {
		b.topics[topic] = Subscribers{}
	}
	s.AddTopic(topic)
	b.topics[topic][s.id] = s
	fmt.Printf("suscriptor %s suscrito al topic: %s\n", s.id, topic)
}

func (b *Broker) RemoveSubscriber(s *Subscriber) {
	// Remover suscriptor del broker (Esto se podría separar, en otra función, para que sea más claro)
	// Desuscribir al suscriptor de todos los temas
	for topic := range s.topics {
		b.Unsubscribe(s, topic)
	}
	b.mut.Lock()
	// Remover al suscriptor del mapa de suscriptores
	delete(b.subscribers, s.id)
	b.mut.Unlock()
	s.Destruct()
}

func (b *Broker) Unsubscribe(s *Subscriber, topic string) { // Desuscribe un broker a un tema/topic

	b.mut.RLock()
	defer b.mut.RUnlock()

	delete(b.topics[topic], s.id)
	s.RemoveTopic(topic)
	fmt.Printf("Sucriptor %s Cancelar suscripcion al topic: %s\n", s.id, topic)
}

func (b *Broker) GetSubscribers(topic string) int { // Retorna el numero de suscriptores en un tema
	b.mut.RLock()
	defer b.mut.RUnlock()
	return len(b.topics[topic])
}

func (b *Broker) Publish(topic string, msg string) { // Envia un mensaje a un tema
	b.mut.RLock()
	bTopics := b.topics[topic]
	b.mut.RUnlock()
	for _, s := range bTopics {
		m := NewMessage(msg, topic)
		if !s.active {
			return
		}
		go (func(s *Subscriber) {
			s.Signal(m)
		})(s)
	}
}

func (b *Broker) Broadcast(msg string, topics []string) { // Envia un mensaje a todos los temas relacionados al mensaje
	for _, topic := range topics {
		for _, s := range b.topics[topic] {
			m := NewMessage(msg, topic)
			go (func(s *Subscriber) {
				s.Signal(m)
			})(s)
		}
	}
}
