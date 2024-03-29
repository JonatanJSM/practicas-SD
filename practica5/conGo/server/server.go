package main

import (
	"log"
	"net"
	"net/http"
	"net/rpc"
	"time"
)

type Args struct{} // Input arguments for the RPC call
type TimeServer int64

func (t *TimeServer) GiveServerTime(args *Args, reply *int64) error {
	// Fill reply pointer to send the data back
	*reply = time.Now().Unix()
	return nil
}
func main() {
	// Create a new RPC server
	timeserver := new(TimeServer)
	// Register RPC server
	rpc.Register(timeserver)
	rpc.HandleHTTP()
	// Listen for requests on port 1234
	l, e := net.Listen("tcp", ":2233")
	if e != nil {
		log.Fatal("listen error:", e)
	}
	http.Serve(l, nil)
}
