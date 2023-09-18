package message;

import com.sun.xml.internal.ws.developer.Serialization;

import java.io.Serializable;
import java.lang.annotation.Annotation;

public class Operator implements Serializable {
    private int id;

    private String name;
    private String country;
    private String creationDate;
    private int countOfUsers;

    public Operator(){
        id = -1;
        name = "";
        country = "";
        creationDate = "2004:04:16";
        countOfUsers = 0;
    }
    /**DEFAULT CREATE*/
    public Operator(String name, String country, String creationDate, int countOfUsers) {
        this.name = name;
        this.country = country;
        this.creationDate = creationDate;
        this.countOfUsers = countOfUsers;
    }
    /**DATABASE CREATE*/
    public Operator(int id, String name, String country, String creationDate, int countOfUsers){
        this.id = id;
        this.name = name;
        this.country = country;
        this.creationDate = creationDate;
        this.countOfUsers = countOfUsers;
    }

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }
    public String getCreationDate() {
        return creationDate;
    }

    public int getCountOfUsers() {
        return countOfUsers;
    }
    public String getCountry() {
        return country;
    }

    @Override
    public String toString() {
        return "Operator{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", country='" + country + '\'' +
                ", creationDate='" + creationDate + '\'' +
                ", countOfUsers=" + countOfUsers +
                '}';
    }
}
