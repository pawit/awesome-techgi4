package superclient;

import supersquare.SuperSquare;
import supersquare.SuperSquareService;

public class SuperClient {

  public static void main(String[] args) throws Exception {
    SuperSquareService sss = new SuperSquareService();
    SuperSquare ss = sss.getSuperSquarePort();

    int squareOf15 = ss.calcSquare(15);

    System.out.println("The square of 15 is: " + squareOf15);
  }
}