import 'package:flutter/material.dart';
import 'package:flash_chat/components/rounded_button.dart';
import 'package:flash_chat/constants.dart';
import 'package:firebase_core/firebase_core.dart';
import 'package:firebase_database/firebase_database.dart';

class LoginScreen extends StatefulWidget {
  static const String id = 'login_screen';

  @override
  _LoginScreenState createState() => _LoginScreenState();
}

class _LoginScreenState extends State<LoginScreen> {
  final DatabaseReference db = FirebaseDatabase.instance.reference();
  var balance;

  void printFirebase() {
    db.once().then((DataSnapshot snapshot) async {
      setState(() {
        balance = snapshot.value["Owner"]["Balance"];
      });
    });
  }

  @override
  Widget build(BuildContext context) {
    printFirebase();
    return Scaffold(
      appBar: AppBar(
        title: Text("Balance"),
      ),
      backgroundColor: Colors.white,
      body: Column(
        mainAxisAlignment: MainAxisAlignment.center,
        crossAxisAlignment: CrossAxisAlignment.stretch,
        children: <Widget>[
          Center(
              child: Text(
            balance.toString(),
            style: kSendButtonTextStyle.copyWith(
              fontSize: 50,
            ),
          )),
        ],
      ),
    );
  }
}
