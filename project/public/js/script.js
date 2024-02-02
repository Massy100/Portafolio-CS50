document.addEventListener("DOMContentLoaded", function () {
    const formPopup = document.querySelector(".form-popup");
    const hidePopupBtn = formPopup.querySelector(".close-btn");
    const signupLoginLink = formPopup.querySelectorAll(".bottom-link a");

    // Mostrar el formulario emergente
    formPopup.classList.add("show-popup");

    // Ocultar el formulario emergente al hacer clic en el botón de cierre
    hidePopupBtn.addEventListener("click", function () {
        formPopup.classList.remove("show-popup");
    });

    // Alternar entre los formularios de inicio de sesión y registro
    signupLoginLink.forEach(link => {
        link.addEventListener("click", (e) => {
            e.preventDefault();
            formPopup.classList.toggle("show-signup");
        });
    });
});