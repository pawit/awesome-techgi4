package supersquare;

import javax.jws.*;

@WebService
public class SuperSquare {

  @WebMethod
  public int calcSquare(int n) {
    return n*n;
  }
}