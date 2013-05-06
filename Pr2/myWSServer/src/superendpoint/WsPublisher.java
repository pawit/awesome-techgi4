package superendpoint;

import javax.xml.ws.Endpoint;
import supersquare.SuperSquare;

public class WsPublisher {

  public static void main(String[] args) {
    Endpoint.publish("http://localhost:8888/supersquare", new SuperSquare());

    System.out.println("Service running!");
  }
}