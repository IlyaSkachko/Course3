
// const { send } = require("m06_siia");

// send("ilya.skachko.03@mail.ru", "yhWiguqs3mcviGuwb0YF", "ilya.skachko.90@mail.ru", "Node js test Lab5")
//     .then((result) => {
//         console.log("Successfully", result)
//     })
//     .catch(err => {
//         console.log("Error", err);
//     });


const { send } = require("m06_sia");

send("ilya.skachko.03@mail.ru", "yhWiguqs3mcviGuwb0YF", "Node js test Lab5")
    .then((result) => {
        console.log("Successfully", result)
    })
    .catch(err => {
        console.log("Error", err);
    });