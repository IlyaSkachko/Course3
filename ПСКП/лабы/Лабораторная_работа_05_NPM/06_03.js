const { send } = require("./m06_SIA");

//yhWiguqs3mcviGuwb0YF

send("ilya.skachko.03@mail.ru", "yhWiguqs3mcviGuwb0YF", "Node js test Lab5")
    .then((result) => {
        console.log("Successfully", result)
    })
    .catch(err => {
        console.log("Error", err);
    });