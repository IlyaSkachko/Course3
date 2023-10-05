function firstJob() {
    return new Promise((resolve, reject) => {
        setTimeout(() => {
            resolve("Hello world!");
        }, 2000);
    });
}

firstJob() 
    .then((result) => {
        console.log(result);
    })
    .catch((error) => {
        console.error(error);
    }); 


async function firstJobAsync() {
    try {
        console.log(await firstJob() + " async");
    } catch (error) {
        console.log(error);
    }
}

firstJobAsync();