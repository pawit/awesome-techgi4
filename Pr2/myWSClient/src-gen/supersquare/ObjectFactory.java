
package supersquare;

import javax.xml.bind.JAXBElement;
import javax.xml.bind.annotation.XmlElementDecl;
import javax.xml.bind.annotation.XmlRegistry;
import javax.xml.namespace.QName;


/**
 * This object contains factory methods for each 
 * Java content interface and Java element interface 
 * generated in the supersquare package. 
 * <p>An ObjectFactory allows you to programatically 
 * construct new instances of the Java representation 
 * for XML content. The Java representation of XML 
 * content can consist of schema derived interfaces 
 * and classes representing the binding of schema 
 * type definitions, element declarations and model 
 * groups.  Factory methods for each of these are 
 * provided in this class.
 * 
 */
@XmlRegistry
public class ObjectFactory {

    private final static QName _CalcSquare_QNAME = new QName("http://supersquare/", "calcSquare");
    private final static QName _CalcSquareResponse_QNAME = new QName("http://supersquare/", "calcSquareResponse");

    /**
     * Create a new ObjectFactory that can be used to create new instances of schema derived classes for package: supersquare
     * 
     */
    public ObjectFactory() {
    }

    /**
     * Create an instance of {@link CalcSquareResponse }
     * 
     */
    public CalcSquareResponse createCalcSquareResponse() {
        return new CalcSquareResponse();
    }

    /**
     * Create an instance of {@link CalcSquare }
     * 
     */
    public CalcSquare createCalcSquare() {
        return new CalcSquare();
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link CalcSquare }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://supersquare/", name = "calcSquare")
    public JAXBElement<CalcSquare> createCalcSquare(CalcSquare value) {
        return new JAXBElement<CalcSquare>(_CalcSquare_QNAME, CalcSquare.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link CalcSquareResponse }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://supersquare/", name = "calcSquareResponse")
    public JAXBElement<CalcSquareResponse> createCalcSquareResponse(CalcSquareResponse value) {
        return new JAXBElement<CalcSquareResponse>(_CalcSquareResponse_QNAME, CalcSquareResponse.class, null, value);
    }

}
