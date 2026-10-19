# Jogo das Moedas - Prática 03 (Coesão e Acoplamento)

**Aluno(s):** Gabriel Henrique Rocha Melo
**Matrícula:** 20250059916
**Versão do JDK:** JDK 25.0.4.1
---

## Observações das Tarefas

### Itens 1 a 3 (Reintegração das Classes)
As classes `GUIRenderer`, `ButtonInputs` e `VirtualJoystickInput` foram totalmente integradas e implementadas utilizando Java Swing básico para permitir a visualização e os controles adequados. 
* O enum `InputsEnum` foi expandido para receber `BUTTONS` e `JOYSTICK`.
* O enum `RendererEnum` recebeu a opção `GUI`.
* As respectivas factories também foram atualizadas para instanciar essas novas classes de acordo com a seleção por linha de comando.

### Item 4 (Independência entre Entrada e Saída)
**Testes executados:**
* `java -cp bin game.MainGame -i buttons -r terminal` -> **Funcionou perfeitamente**.
* `java -cp bin game.MainGame -i keyboard -r gui` -> **Funcionou perfeitamente**.
* `java -cp bin game.MainGame -i joystick -r terminal` -> **Funcionou perfeitamente**.

**Conclusão:** 
Essas execuções provam que o **acoplamento** entre a entrada (`IInputs`) e a saída (`IRenderer`) do jogo é inexistente do ponto de vista de lógica. A classe `Level` conversa apenas com as interfaces e independe totalmente do dispositivo que está enviando os comandos ou desenhando a tela. Isso demonstra na prática o sucesso do princípio de Inversão de Dependência, possibilitando a troca de módulos sem quebrar ou alterar a regra de negócio central.

### Item 5 (Estratégia de Idiomas)
**Arquitetura:**
* Criado o enum `LanguageEnum` (`ENGLISH`, `PORTUGUESE`, `SPANISH`).
* Criada a classe abstrata `Language` que gerencia e encapsula uma instância de `IRenderer`.
* Criadas três subclasses concretas para implementar os textos específicos de cada idioma.
* Criada `LanguageFactory` implementando a interface `IFactory<Language, LanguageEnum>`.
* A classe `MainGame` foi atualizada para processar a *flag* `-lang` e instanciar a linguagem. 

**Por que o contrato de idioma deve ser uma classe abstrata (ou interface)?**
O contrato de idioma define um modelo (template) comportamental, onde cada implementação específica só altera as strings a serem impressas, mas a forma de imprimi-las (usando um `IRenderer`) permanece idêntica. Ao utilizarmos uma classe abstrata injetando a dependência de `IRenderer` no construtor da classe base, evitamos o incômodo e a repetição de passar o renderizador manualmente por parâmetro para todos os métodos. Caso usássemos apenas uma `interface ILanguage`, o parâmetro de `renderer` seria espalhado redundantemente por todas as chamadas.

### Alterações em Arquivos de Regra Exigidas e Justificativas:
* **`IRenderer.java`**: Adicionado o método abstrato `showPrompt(String message)`. 
  * *Justificativa:* Anteriormente o método `TerminalRenderer.draw` estava fazendo hardcode dos textos (`System.out.println("Score: " + ...)` e `System.out.print("Comando...")`). Essa alteração retira esses textos dali e cria uma porta de saída adequada para textos de linha contínua, permitindo que a própria classe `Language` imprima as pontuações e comandos pelo `showPrompt`.
* **`Level.java`**: O construtor foi atualizado para receber o `Language`. O uso local de `renderer.showMessage` (com strings hardcoded em inglês) foi substituído por invocações aos métodos de `Language` (ex: `language.printWall()`).
* **`TerminalRenderer.java`**: Modificado para remover os prints fixos de `Score` e `Comando`. 

---
