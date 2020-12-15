fs = require('fs');

const input = fs.readFileSync('./1input.txt', {encoding: 'utf-8'});
const numbers = input.split('\n');
console.log(numbers.length);

//console.log(numbers[0])
//console.log(numbers[199])
//console.log(numbers[200])

//brute force find two
//for (var i = 0; i<=199; i++) {
    //const num = +numbers[i];
    //for(var j = i; j<=199; j++) {
      //const num2 = +numbers[j];
        //if(num2 + num === 2020) {
            //console.log(num, num2);
            //console.log(num * num2);
        //}
  //}
//}
// fast find 2
//const map = {};

//for (num in numbers) {
    //map[+numbers[num]] = true;
    //if(map[2020 - +numbers[num]]) {
        //console.log(+numbers[num]);
        //console.log(2020 - +numbers[num]);
        //console.log(num + +numbers[num])
    //} 
//}

//console.log(map);
//
//find 3

numbers.forEach((num, i) => {
    for (var j = i; j <= 199; j++) {
        var num2 = +numbers[j];
        //if (+num + num2 < 2020) {
            for (var k = j; k <= 199; k++) {
                var num3 =  +numbers[k];
                //console.log(num, num2, num3);
                if(+num + num2 + num3 === 2020) {
                    console.log(num, num2, num3);
                    console.log(num * num2 * num3);
                }
            }
        //}
    }
})
