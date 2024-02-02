let tiempoInicio;
    let intervaloCronometro;
    let totalTiempoEstudio = 0;
    let cantidadSesiones = 0;

    function iniciarCronometro() {
        tiempoInicio = new Date().getTime();
        intervaloCronometro = setInterval(actualizarCronometro, 1000);
    }

    function actualizarCronometro() {
        const tiempoActual = new Date().getTime();
        const tiempoTranscurrido = tiempoActual - tiempoInicio;

        const segundos = Math.floor(tiempoTranscurrido / 1000);
        const minutos = Math.floor(segundos / 60);
        const horas = Math.floor(minutos / 60);

        const tiempoFormateado = pad(horas) + ":" + pad(minutos % 60) + ":" + pad(segundos % 60);

        document.getElementById("cronometro").innerHTML = tiempoFormateado;
    }

    function pad(valor) {
        return valor < 10 ? "0" + valor : valor;
    }

    // Función para actualizar las estadísticas
    function actualizarEstadisticas() {
        totalTiempoEstudio += tiempoInicio ? new Date().getTime() - tiempoInicio : 0;
        cantidadSesiones++;

        const tiempoTotalFormateado = formatTiempo(totalTiempoEstudio);
        const promedioDiarioFormateado = cantidadSesiones ? formatTiempo(totalTiempoEstudio / cantidadSesiones) : "00:00:00";

        document.getElementById("totalEstudio").innerHTML = tiempoTotalFormateado;
        document.getElementById("promedioDiario").innerHTML = promedioDiarioFormateado;
    }

    // Llama a actualizarEstadisticas cada minuto
    setInterval(actualizarEstadisticas, 100);

    // Formatea el tiempo en segundos a HH:mm:ss
    function formatTiempo(tiempoEnMilisegundos) {
        const segundos = Math.floor(tiempoEnMilisegundos / 1000);
        const minutos = Math.floor(segundos / 60);
        const horas = Math.floor(minutos / 60);

        return pad(horas) + ":" + pad(minutos % 60) + ":" + pad(segundos % 60);
    }