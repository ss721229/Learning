'use strict'; // 이걸 넣으면, 코드 작성에 있어서 문법에 더 신경써야 한다.

/* <1강> async와 defer의 차이점
- async : HTML의 실행과 js의 설치가 같이 진행되며, js 설치가 됨과 동시에 실행된다.
실행되는 동안에는 HTML 실행이 멈춘다. HTML이 실행 완료되기 전에 js가 실행되므로,
HTML에서 사용하려는 요소가 아직 정의 되지 않았을 수 있다.
참고 : js가 여러개 있으면, 각각 설치가 먼저되는 것이 먼저 실행되므로 순서에
의존적인 js라면 원하는대로 동작하지 않을 수 있다.

- defer : HTML의 실행과 js의 설치가 같이 진행되며, HTML 실행이 끝난 뒤에 js 실행이 진행된다. */


console.log('<3강>');
let globalName="global sangmin"; // 전역변수 (global 변수)
{ // 중괄호 안에 있는 변수는 이 안에서만 유효하다.(block)
  let name = "sangmin";
  console.log(name);
  name= "hello";
  console.log(name);
}
console.log(name); // 출력 안됨
console.log(globalName); // 출력 됨

{
  age = 4;
  var age;
}
console.log(age);

console.log('number');
const count = 17; // integer
const size = 17.1; // decimal num
const infinity = 1 / 0; // +무한대
const negativeInfinity = -1 / 0; // -무한대
const nAn = 'not a number' / 2;
// 글자와 숫자는 연산이 불가능 하기 때문에 NaN이 출력된다.
console.log(`value: ${count}, type: ${typeof count}`);
console.log(`value: ${size}, type: ${typeof size}`);
console.log(infinity);
console.log(negativeInfinity);
console.log(nAn);

console.log('string');
const char = 'c';
const brendan = 'brendan'
const greeting = 'hello' + brendan;
console.log(`value: ${greeting}, type: ${typeof greeting}`);
const helloBob = `hi ${brendan}!`;
console.log('value: '+helloBob+' type: '+typeof helloBob);

console.log('dyanmic typing');
let text = 'hello';
console.log(`value: ${text}, type: ${typeof text}`);
text = 1;
console.log(`value: ${text}, type: ${typeof text}`); // type 변경이 가능하다.
text = '7' + 5;
console.log(`value: ${text}, type: ${typeof text}`); // 문자와 숫자의 계산은 문자로 합쳐진다.
text = '8' / '2';
console.log(`value: ${text}, type: ${typeof text}`); // 문자와 문자의 계산은 숫자로 계산된다.

/* <3강> data types, let vs var, hoisting
- var은 쓰면 안된다. 대신에 let을 쓰자.
=> hoisting(선언 순서에 상관없이 선언을 맨 위로 끌어올린다.)
=> 블럭 안에 있어도, 전역변수처럼 활용 가능하다.

- const 변수는 한번 선언하면 값을 변경할 수 없다.
=> security, thread safety, reduce human mistakes
*/