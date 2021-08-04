'use strict';

// 1. String concatenation
// 참고: empty string (''),null, underined, 0은 false로 간주된다.
console.log('my' + ' cat');
console.log('1' + 2 );
console.log(`string literals: 1 + 2 = ${1 + 2}`);
console.log("ellie's \nbook");

// 2. Numeric operators
console.log(2+3);
console.log(2-3);
console.log(2*3);
console.log(2/3);
console.log(2%3);
console.log(2**3);

// 3. Increment and decrement operators
let counter = 2;
const preIncrement = ++counter;
console.log('(pre)counter = '+ counter);
// counter = counter + 1;
// preIncrement = counter;

const postIncrement = counter++;
console.log('(post)counter = '+ counter);
// preIncrement = counter;
// counter = counter + 1;

// 4. Assignment operators
let x = 3;
let y = 6;
x += y;
x -= y;
x *= y;
x /= y;

// 5. Comparison operators (부등호)

// 6. Logical operators: || or , && and , ! not
// or은 앞에서 true가 되면 뒤에거는 확인 X, and는 모두 확인

// 7. Equality
const stringFive = '5';
const numberFive = 5;

// == loose equality, with type conversion
// 타입이 달라도 같은 문자면 true
console.log(stringFive == numberFive);
console.log(stringFive != numberFive);

// == strict equality, no type conversion
// 타입이 다르면 False
console.log(stringFive === numberFive);
console.log(stringFive !== numberFive);

const ellie1 = { name: 'ellie'};
const ellie2 = { name: 'ellie'};
const ellie3 = ellie1;
console.log(ellie1 == ellie2);
console.log(ellie1 === ellie2);
console.log(ellie1 === ellie3);

// 8. Conditional operators : if, else if, else

// 9. Conditional operators : ?
const name="ellie";
console.log(name === 'ellie' ? 'yes' : 'no');
// true면 왼쪽, false면 오른쪽이 실행된다.

// 10. Switch statement
const browser = 'IE';
switch (browser) {
  case 'IE':
    console.log('go away!');
    break;
  case 'Chrome':
  case 'Firefox':
    console.log('love you!');
      break;
}

// 11. Loops : while, do while, for, break, continue

