package message.test;

import com.sun.messaging.BasicConnectionFactory;
import com.sun.messaging.ConnectionConfiguration;
import com.sun.messaging.ConnectionFactory;

import javax.jms.*;

public class TestOut {

    public static void main(String[] args){
        ConnectionFactory factory = new ConnectionFactory();

        try (JMSContext context = factory.createContext("admin", "admin")){
            factory.setProperty(ConnectionConfiguration.imqAddressList, "mq://127.0.0.1:7676, mq://127.0.0.1:7676");

            Destination cardsQueue = context.createQueue("BankCardQueue");
            JMSProducer producer = context.createProducer();

            producer.send(cardsQueue, "PNV 100 5634234");

            System.out.println("Placed an information about card transaction to BankCardQueue");
        }
        catch (JMSException err) {
            System.out.println(err.getMessage());
        }
    }
}
