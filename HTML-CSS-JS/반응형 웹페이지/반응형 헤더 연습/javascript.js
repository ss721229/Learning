const toggleBtn = document.querySelector('.nav__toggleBtn');
const menu = document.querySelector('.nav__menu');
const links = document.querySelector('.nav__links');

toggleBtn.addEventListener('click',() => {
  menu.classList.toggle('active');
  links.classList.toggle('active');
});
