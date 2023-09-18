

function thirdJob(data) {
    return new Promise((resolve, reject) => {
        if (isNaN(data)) {
            reject("error");
        } else if (data % 2 !== 0) {
            setTimeout(() => {
                resolve("odd");
            })
        } else if (data % 2 === 0) {
            setTimeout(() => {
                reject("even");
            })
        }
    });
}


thirdJob(3)
    .then((result) => {console.log(result)})
    .catch(error => {console.error(error)});


async function thirdJobAsync() {
    try {
        console.log(await thirdJob("g"));
    } catch (error) {
        console.log(error);
    }
}


thirdJobAsync();