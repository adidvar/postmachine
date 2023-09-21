#include "postmachine.hpp"

void PostMachine::nextStep()
{
    auto &command = m_commands[m_command_index];
    size_t jump = m_command_index + 1;
    if (command.getJump1() != Command::kinvalid_jump)
        jump = command.getJump1();

    switch (command.getType()) {
    case Command::MoveLeft:
        m_tape.setHead(m_tape.getHead() - 1);
        break;
    case Command::MoveRight:
        m_tape.setHead(m_tape.getHead() + 1);
        break;
    case Command::WriteZero:
        m_tape.writeOnHead(0);
        break;
    case Command::WriteOne:
        m_tape.writeOnHead(1);
        break;
    case Command::MoveIF:
        jump = m_tape.readOnHead() ? command.getJump1() : command.getJump2();
        break;
    case Command::End:
        break;
    case Command::Invalid:
        //TODO
        break;
    }

    m_command_index = jump;
}

void PostMachine::reset()
{
    m_command_index = 0;
}

bool PostMachine::isEnd() const
{
    return m_commands[m_command_index].getType() == Command::End;
}

size_t PostMachine::getCommandIndex() const
{
    return m_command_index;
}

QVector<Command> PostMachine::getCommands() const
{
    return m_commands;
}

Tape PostMachine::getTape() const
{
    return m_tape;
}

void PostMachine::setCommandIndex(size_t index)
{
    m_command_index = index;
}

void PostMachine::setCommands(const QVector<Command> &commands)
{
    m_commands = commands;
}

void PostMachine::setTape(const Tape &tape)
{
    m_tape = tape;
}
