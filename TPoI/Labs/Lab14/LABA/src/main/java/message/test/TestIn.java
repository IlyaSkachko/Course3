package message.test;
import javax.jms.*;

import com.sun.messaging.ConnectionConfiguration;
import com.sun.messaging.ConnectionFactory;

public class TestIn implements MessageListener {
    ConnectionFactory factory = new com.sun.messaging.ConnectionFactory();
    JMSConsumer consumer;
    public void DirectMessageReceiver() {
        try (JMSContext context = factory.createContext("admin", "admin")) {
            factory.setProperty(ConnectionConfiguration.imqAddressList,
                    "mq://127.0.0.1:7676,mq://127.0.0.1:7676");
            Destination cardsQueue = (Destination) context.createQueue("BankCardQueue");
            consumer = context.createConsumer(cardsQueue);
            consumer.setMessageListener(this);
            System.out.println("Listening to theBankCardQueue...");
        // wait for messages
            Thread.sleep(100000);
        } catch (InterruptedException | JMSException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        TestIn a = new TestIn();

        a.DirectMessageReceiver();
    }

    @Override
    public void onMessage(Message msg) {
        try{
            System.out.println("Got the text message from the BankCardQueue: " +
                    msg.getBody(String.class));
            System.out.println("\n Here's what toString() on the message prints \n" + msg);
        } catch (JMSException e){
            System.err.println("JMSException: " + e.toString());
        }
    }
}
