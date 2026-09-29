# Lab 2: Architectural Design and Software Detailed Design

This lab is designed to help you understand the concepts of software architecture and detailed design.

🟢 __Simple__: A guided software engineering activity that introduces the basic concepts step by step. It should not take more than 15 - 20 minutes to finish.

🟡 __Moderate__: A software engineering activity that asks you to apply the concepts to a realistic team or project situation. These tasks can usually be completed in about 30 - 45 minutes, depending on your prior knowledge.

🔴 __Complex__: A more demanding or longer software engineering activity that requires you to combine concepts, make decisions as a team, and work through a broader project context. Such tasks might take up to a few hours to complete.


## 🟢 Section I: UML Use-Case Diagrams

In this exercise, you will practice creating a UML use-case diagram from a short system description.
The goal is to identify actors and use-cases, and to model meaningful `include` and `extend` relationships.

### Task Description

Model the following system as a UML use-case diagram in Draw.io.

#### System: Online Pizza Ordering

A small pizza restaurant wants to offer an online ordering system.
Customers can browse the menu, customize a pizza, place an order, pay online, and track the order status.
The kitchen staff prepares accepted orders, and a delivery driver delivers orders that are marked for delivery.

The system should support the following behavior:

* A customer can browse the menu without logging in.
* A customer must log in before placing an order.
* When placing an order, the customer must choose either pickup or delivery.
* Every order must include selecting items from the menu and confirming the order summary.
* If the customer chooses delivery, the system also asks for a delivery address.
* The customer may optionally apply a discount code during checkout.
* The customer pays online after confirming the order.
* Kitchen staff can view new orders and mark an order as being prepared.
* Kitchen staff can mark an order as ready.
* A delivery driver can view orders ready for delivery and mark them as delivered.
* A customer can track the current order status.

#### 1. Identify Actors

Identify all external actors that interact with the online ordering system.

#### 2. Identify Use-Cases

List the main use-cases that should appear in the diagram.

#### 3. Add Relationships

Create the use-case diagram and include at least:

* Two `include` relationships for behavior that is always part of another use-case
* Two `extend` relationships for optional or conditional behavior

Label the actors, use-cases, and relationships clearly.


## 🟢 Section II: UML Sequence Diagrams

In this exercise, you will practice creating a UML sequence diagram from textual requirements.
The goal is to identify the participating actors and system components, model the order of messages, and show important decisions in the interaction.

### Task Description

Model the following system behavior as a UML sequence diagram and model it in Draw.io.

#### System: Library Book Reservation

A university library offers a web application where students can reserve books.
The reservation process should work as follows:

* A student searches for a book by entering a title, author, or ISBN.
* The library web application sends the search request to the library catalog.
* The catalog returns a list of matching books with their availability status.
* The student selects one available book and requests a reservation.
* The web application checks whether the student is logged in.
* The account service verifies that the student has not exceeded the maximum number of active reservations.
* If the account is valid, the web application creates a reservation in the reservation service.
* The reservation service marks the selected book as reserved in the catalog.
* The reservation service sends a confirmation email to the student.
* The web application shows a reservation confirmation with the pickup deadline.
* If the selected book is no longer available, the web application informs the student and asks them to select another book.
* If the account check fails, the web application shows the reason why the reservation cannot be completed.

#### 1. Identify Participants

Identify the actors and system components that should appear as lifelines in your sequence diagram.

#### 2. Model the Main Success Scenario

Create a sequence diagram for the successful reservation of an available book by a student with a valid account.


#### 3. Add Alternatives

Extend your diagram with alternative paths.

* The selected book is no longer available
* The student's account check fails

Use UML combined fragments.


## 🟢 Section III: Layered Architecture

In this exercise, you will apply the idea of layered architecture to a familiar system.
The goal is to decide which responsibilities belong in which layer and to reason about the dependencies between layers.

### Task Description

Design a layered architecture for the following system.

#### System: Simple Online Shop

You are designing a simple online shop.
The system must:

* Display products with current availability
* Allow users to place orders
* Calculate prices, discounts, tax, and shipping costs
* Validate whether enough stock is available before confirming an order
* Store products, orders, customers, and payments in a database
* Send an order confirmation after successful checkout
* Allow administrators to update product data

#### 1. Design the Layers

Create a layered architecture.
For each layer, describe its main responsibility and assign the features above to the correct layer.

E.g.:
* Which layer should contain business rules such as discount calculation and stock validation?
* Which layer should communicate with the database?
* ...

#### 2. Draw Dependencies

Draw the allowed dependencies between the layers.

#### 3. Reflect on the Design

Answer the following questions:

* Would you choose closed or open layering?
* What is one benefit of your design?
* What is one drawback of your design?
* A teammate suggests that the product page should directly query the database because it would be faster. Do you agree? Explain your decision using layered architecture.


## 🟡 Section IV: UML Component Diagrams

In this exercise, you will practice creating a UML component diagram from a short architectural description.
The goal is to identify software components, their interfaces, and the dependencies between them.

### Task Description

Model the following system as a UML component diagram in Draw.io.

#### System: Campus Event Management Platform

A university wants to build a campus event management platform.
Students can browse upcoming events, register for events, receive notifications, and cancel registrations.
Event organizers can create events, update event details, view attendee lists, and check students in at the event.
Administrators can approve new events before they are published.

Students access the platform through a Web Frontend or a Mobile App.
Both clients communicate with an Event Management Service to browse event information.
Event organizers also use the Event Management Service to create events, update event details, view attendee lists, and check students in at the event.
The Event Management Service stores and reads event data from an Event Database and can request calendar entries from an External Calendar Service.

Event registrations are handled by a separate Registration Service.
When a student registers for or cancels an event, the Registration Service checks the student's login status through a User Account Service.
It then stores registration data in the Event Database.

Before an event becomes visible to students, an administrator must approve it through an Approval Service.
After a successful registration or cancellation, a Notification Service sends a message to the student through an External Email Gateway.

The backend services use a shared configuration artifact named `campus-events-config.yaml`.
This configuration file contains the database connection name, the endpoint of the User Account Service, the endpoint of the External Email Gateway, and the endpoint of the External Calendar Service.
The Event Management Service, Registration Service, and Notification Service read this configuration file when they start.

#### 1. Identify Components

Identify the software components described in the scenario that should appear in the component diagram and add them to your diagram.

#### 2. Define Interfaces

Add provided and required interfaces for the most important interactions to your diagram.

#### 3. Draw Dependencies

Show the dependencies between components in your diagram.

Use cylinders for databases even if they are not standard UML components.

