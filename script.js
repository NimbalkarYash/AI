function toggleChat() {

    let chat = document.getElementById("chatbox");

    if(chat.style.display === "none" || chat.style.display === "") {

        chat.style.display = "block";
    }
    else {

        chat.style.display = "none";
    }
}

function sendMessage() {

    let input = document.getElementById("userInput");

    let message = input.value.trim();

    if(message === "") return;

    displayMessage(message, "user-message");

    let response = getResponse(message.toLowerCase());

    setTimeout(() => {

        displayMessage(response, "bot-message");

    }, 500);

    input.value = "";
}

function displayMessage(message, className) {

    let messages = document.getElementById("messages");

    let div = document.createElement("div");

    div.className = className;

    div.innerText = message;

    messages.appendChild(div);

    messages.scrollTop = messages.scrollHeight;
}

document.getElementById("userInput")
.addEventListener("keypress", function(event) {

    if(event.key === "Enter") {

        sendMessage();
    }
});

function getResponse(message) {

    if(message.includes("membership") ||
       message.includes("fees") ||
       message.includes("plan")) {

        return "We offer:\nMonthly: ₹999\n3 Months: ₹2499\nYearly: ₹8999";
    }

    else if(message.includes("monthly")) {

        return "Monthly Plan costs ₹999 per month.";
    }

    else if(message.includes("3 month") ||
            message.includes("three month")) {

        return "3-Month Plan costs ₹2499.";
    }

    else if(message.includes("yearly")) {

        return "Yearly Plan costs ₹8999.";
    }

    else if(message.includes("timing") ||
            message.includes("hours")) {

        return "We are open from 5 AM to 11 PM.";
    }

    else if(message.includes("trainer")) {

        return "Yes! Certified trainers are available.";
    }

    else if(message.includes("diet")) {

        return "We provide diet guidance for premium members.";
    }

    else if(message.includes("weight loss")) {

        return "We have dedicated weight loss programs.";
    }

    else if(message.includes("muscle")) {

        return "We provide muscle gain and strength programs.";
    }

    else if(message.includes("equipment")) {

        return "We have treadmills, benches, weights, and modern machines.";
    }

    else if(message.includes("trial")) {

        return "Yes! We offer a 1-day free trial.";
    }

    else if(message.includes("contact") ||
            message.includes("phone")) {

        return "You can contact us at 9876543210.";
    }

    else if(message.includes("location") ||
            message.includes("address")) {

        return "We are near Elpro City Square Mall, Chinchwad.";
    }

    else {

        return "Sorry, I didn't understand that.";
    }
}