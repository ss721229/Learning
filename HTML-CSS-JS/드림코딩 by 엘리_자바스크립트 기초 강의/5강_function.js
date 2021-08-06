"use strict";
// 1. Function declaration
// one function === one thing
// naming : doSomething, command, verb
// e.g. createCardAndPoint -> createCard, createPoint
// function is object in JS

function printHello(){
    console.log('Hello');
}
printHello();

function log(message){
    console.log(message);
}
log('Hello@');

// 2. Parameters
// premitive parameters: passed by value
// object parameter: passed by reference
function changeName(obj) {
    obj.name = 'coder';
}
const ellie = { name: 'ellie'};
changeName(ellie);
console.log(ellie);

// 3. Default Parameters ( added in ES6)
// 파라미터 값을 넣지 않았을 때, 뒤에 있는 값이 대체되어서 사용됨.
function showMessage(message, from = 'unknown'){
    console.log(`${message} by ${from}`);
}
showMessage('Hi');

// 4. Rest parameters ( added in ES6 )
function printAll(...args) {
    for(let i = 0; i < args.length; i++)
        console.log(args[i]);
    
    for(const arg of args)
        console.log(arg);
    
    args.forEach((arg) => console.log(arg));
}
printAll('dream','coding','ellie');

// 5. Local scope
let blobalMessage = 'blobal'; // global variable
function printMessage() {
    let message = 'hello'; // local variable
    console.log(message);
    // console.log(globalMessage); -> 오류 발생
    function printAnother() {
        let childmassage = 'hello'; // local variable
        console.log(childmassage);
        console.log(message);
    }
    // console.log(childmassage); -> 오류 발생
}
printMessage();

// 6. return a value
function sum(a,b) {
    return a+b;
}
console.log(sum( 1, 1));

// 7. Early return, early exit
// bad
function upgradeUser(user) {
    if (user.point > 10) {
    // long upgrade logic...
    }
}

// good
// 조건이 맞지 않을 때는 빠르게 함수를 종료함.
function upgradeUser(user) {
    if (user.point <= 10) {
        return;
    }
    // long upgrade logic...
}

// 8. Function expression
// a function declaration can be called earlier than it is defiend. (hoisted)
// a function expression is created when the execution reaches it.
const print = function () { // anonymous function
    console.log('print');
};
print();
const printAgain = print;
printAgain();
const sumAgain = sum;
console.log(sumAgain(1,3));

// 9. callback function using function expression
function randomQuiz(answer, printYes, printNo) {
    if (answer === 'love you')
        printYes();
    else
        printNo();
}

// anonymous function
const printYes = function () {
    console.log('yes!');
}
// named function
// better debugging in debugger's stack traces
// recursions
const printNo = function print() {
    console.log('no!');
}
randomQuiz('wrong', printYes, printNo);
randomQuiz('love you',printYes, printNo);

// 10. Arrow function
// always anonymous
const simplePrint = function () {
    console.log('simplePrint!');
}; // === const simplePrint = () => console.log('simplePrint!');
const add = (a, b) => a + b;

// 11. IIFE: immediately Invoked Function Expression
(function hello() {
    console.log('IIFE');
})();

// Quiz : calculate(command, a, b)
// command: add, substract, divide, multiply, remainder)

function calculate(command, a, b) {
    switch(command) {
        case ('add'):
            console.log(a+b);
            break;
        case ('substract'):
            console.log(a-b);
            break;
        case ('divide'):
            console.log(a/b);
            break;
        case ('multiply'):
            console.log(a*b);
            break;
        case ('remainder'):
            console.log(a/b);
            break;
        default:
            console.log('enter right command');
    }
}