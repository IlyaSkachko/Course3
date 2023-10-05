
const EventEmmiter = require("events");

let db_data = [
    {id: 1, name: "Alex D", bday: "2001-01-01"},
    {id: 2, name: "Vlad M", bday: "2002-02-02"},
    {id: 3, name: "Vanya G", bday: "2003-03-03"}
];

class DB extends EventEmmiter {

    async select() {
        return db_data;
    }

    async insert(object) {
        db_data.push(object);
    }

    async update(object) {
        const index = db_data.findIndex(item => item.id === Number.parseInt(object.id));
        if (index !== -1) {
            db_data[index] = object;
        }
    }

    async delete(id) {
        db_data = db_data.filter(item => item.id !== Number.parseInt(id));
        return db_data;
    }

}

exports.DB = DB;