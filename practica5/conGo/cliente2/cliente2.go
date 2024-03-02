package main

import (
	"fmt"
	"log"
	"net/rpc"
	"strings"
)

// Definir la estructura de los argumentos de la conversión
type ConversionArgs struct {
	Value    float32
	UnitFrom string
	UnitTo   string
}

func main() {
	// Conectar al servidor
	client, err := rpc.Dial("tcp", "localhost:1234")
	if err != nil {
		log.Fatal("dialing:", err)
	}
	defer client.Close() // Cerrar la conexión al finalizar, esto asegura que se deje de usar
	var value float32
	var unitFrom, unitTo string

	fmt.Print("Ingrese el valor a convertir: ")
	// El Scan retorna dos valores, el "_" es para omitir el primero y quedarse con el error
	_, err = fmt.Scan(&value)
	if err != nil {
		log.Fatal("Valor inválido:", err)
	}

	fmt.Print("Ingrese la unidad de origen (pulgada, pie, yarda, milla): ")
	_, err = fmt.Scan(&unitFrom)
	if err != nil {
		log.Fatal("Unidad de origen inválida:", err)
	}

	fmt.Print("Ingrese la unidad de destino (cm, m, km): ")
	_, err = fmt.Scan(&unitTo)
	if err != nil {
		log.Fatal("Unidad de destino inválida:", err)
	}

	// Realizar la conversión
	args := &ConversionArgs{Value: value, UnitFrom: strings.ToLower(unitFrom), UnitTo: strings.ToLower(unitTo)}
	var result float32
	// Llamar al método Conversion del servidor
	err = client.Call("Converter.Conversion", args, &result)
	if err != nil {
		log.Fatal("Conversión fallida:", err)
	}

	fmt.Printf("Resultado: %.2f %s\n", result, unitTo)
}
