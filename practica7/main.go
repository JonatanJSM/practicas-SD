package main

import (
	"database/sql"
	"fmt"
	"log"
	"math/rand"
	"practica7/pubsub"
	"time"

	_ "github.com/go-sql-driver/mysql"
)

var availableTopics = map[string]string{
	"RB": "Rubius",
	"DP": "DuaLipa",
	"LC": "LuisitoComunica",
	"FD": "FaridDieck",
}

func DbConection() *sql.DB {
	//Configura la cadena de conexión a tu base de datos MySQL
	dsn := "root:@tcp(localhost:3306)/sistemasDistribuidos"

	// Abre la conexión con la base de datos
	db, err := sql.Open("mysql", dsn)
	if err != nil {
		log.Fatal(err)
	}
	return db
}

func chanelPublisher(broker *pubsub.Broker) {
	topicKeys := make([]string, 0, len(availableTopics))
	topicValues := make([]string, 0, len(availableTopics))
	mensaje := "NuevasPruebas"
	temas := []string{"RB", "LC"}
	tema := "RB"

	//publish prueba-----------------------
	dbConection := DbConection()
	query := "INSERT INTO youTube (tema, mensaje, fecha) VALUES (?, ?, NOW())"
	_, err := dbConection.Exec(query, tema, mensaje)

	if err != nil {
		log.Fatal(err)
	}

	//final publish prueba----------------

	//broadcast prueba-----------------------
	if len(temas) != 0 {
		for _, temaFor := range temas {
			query := "INSERT INTO youTube (tema, mensaje, fecha) VALUES (?, ?, NOW())"
			_, err := dbConection.Exec(query, temaFor, mensaje)

			if err != nil {
				log.Fatal(err)
			}
		}
	}
	//final broadcast prueba------------------

	for k, v := range availableTopics {
		topicKeys = append(topicKeys, k)
		topicValues = append(topicValues, v)
	}
	for {
		randValue := topicValues[rand.Intn(len(topicValues))] // all topic values.
		msg := fmt.Sprintf("%f", rand.Float64())
		// fmt.Printf("Publishing %s to %s topic\n", msg, randKey)
		go broker.Publish(randValue, msg)
		// Uncomment if you want to broadcast to all topics.
		// go broker.Broadcast(msg, topicValues)
		r := rand.Intn(4)
		time.Sleep(time.Duration(r) * time.Second) //sleep for random secs.
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
