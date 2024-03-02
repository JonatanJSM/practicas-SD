package main

import (
	"errors"
	"net"
	"net/rpc"
)

type ConversionArgs struct {
	Value    float32
	UnitFrom string
	UnitTo   string
}

type Converter int

// Conversion realiza la conversión de unidades de longitud
func (c *Converter) Conversion(args *ConversionArgs, result *float32) error {
	const (
		inchToCm = 2.54
		footToCm = 30.48
		yardToCm = 91.44
		mileToKm = 1.60934
	)

	switch args.UnitFrom {
	case "pulgada":
		switch args.UnitTo {
		case "cm":
			*result = args.Value * inchToCm
		default:
			return errors.New("unidad de destino no válida")
		}
	case "pie":
		switch args.UnitTo {
		case "cm":
			*result = args.Value * footToCm
		case "m":
			*result = args.Value * 0.3048
		case "km":
			*result = args.Value * 0.0003048
		default:
			return errors.New("unidad de destino no válida")
		}
	case "yarda":
		switch args.UnitTo {
		case "cm":
			*result = args.Value * yardToCm
		case "m":
			*result = args.Value * 0.9144
		case "km":
			*result = args.Value * 0.0009144
		default:
			return errors.New("unidad de destino no válida")
		}
	case "milla":
		switch args.UnitTo {
		case "km":
			*result = args.Value * mileToKm
		default:
			return errors.New("unidad de destino no válida")
		}
	default:
		return errors.New("unidad de origen no válida")
	}
	return nil
}

func main() {
	// Crear un servidor RPC
	converter := new(Converter)
	// Registrar el objeto de conversión
	rpc.Register(converter)

	// Escuchar en el puerto 1234
	listener, err := net.Listen("tcp", ":1234")
	if err != nil {
		// Si hay un error al escuchar, terminar el programa
		panic(err)
	}
	defer listener.Close()

	// Aceptar conexiones entrantes
	rpc.Accept(listener)
}
