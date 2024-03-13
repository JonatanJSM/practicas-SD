package main

import (
	"fmt"
	"math/rand"
	"practica7/pubsub"
	"time"
)

var availableTopics = map[string]string{
	"RB": "Rubius",
	"DP": "DuaLipa",
	"LC": "LuisitoComunica",
	"FD": "FaridDieck",
}

var availableMessages = map[string]string{
	"1": "Ha subido un nuevo video",
	"2": "Ha Iniciado un live",
	"3": "Ha muerto",
	"4": "Te ha mencionado",
}

func chanelPublisher(broker *pubsub.Broker) {
	topicValues := make([]string, 0, len(availableTopics))
	messagesValues := make([]string, 0, len(availableMessages))

	for _, v := range availableTopics {
		topicValues = append(topicValues, v)
	}

	for _, v := range availableMessages {
		messagesValues = append(messagesValues, v)
	}

	for {
		randValue := topicValues[rand.Intn(len(topicValues))]
		msg := messagesValues[rand.Intn(len(messagesValues))]

		go broker.Publish(randValue, msg)

		r := rand.Intn(2)
		time.Sleep(time.Duration(r) * time.Second) //Espera por unos segundos.
	}
}

func main() {
	broker := pubsub.NewBroker()

	// Crear suscriptores 1 y 2
	suscriptor1 := broker.AddSubscriber()
	suscriptor2 := broker.AddSubscriber()
	// Suscribir a los temas disponibles
	broker.Subscribe(suscriptor1, availableTopics["RB"])
	broker.Subscribe(suscriptor2, availableTopics["DP"])

	// Crear suscriptores 1 y 2
	suscriptor3 := broker.AddSubscriber()
	suscriptor4 := broker.AddSubscriber()
	// Suscribir a los temas disponibles
	broker.Subscribe(suscriptor3, availableTopics["LC"])
	broker.Subscribe(suscriptor4, availableTopics["FD"])

	go (func() {
		// Sleep por 3 seg, y luego suscribir a s2 para el tema/topic LC
		time.Sleep(3 * time.Second)
		broker.Subscribe(suscriptor2, availableTopics["LC"])
	})()

	go (func() {
		// Sleep por 5 seg y luego desuscribir a s2 para el tema/topic LC
		time.Sleep(5 * time.Second)
		broker.Unsubscribe(suscriptor2, availableTopics["LC"])
		fmt.Printf("El total de suscriptores LC es %v\n", broker.GetSubscribers(availableTopics["LC"]))
	})()

	go (func() {
		time.Sleep(4 * time.Second)
		broker.Subscribe(suscriptor4, availableTopics["LC"])
		fmt.Printf("El total de suscriptores LC es %v\n", broker.GetSubscribers(availableTopics["LC"]))
	})()

	// Concurrently publish the values.
	go chanelPublisher(broker)

	go suscriptor1.Listen()
	go suscriptor2.Listen()
	go suscriptor3.Listen()
	go suscriptor4.Listen()

	fmt.Scanln()
	fmt.Println("Done!")
}
