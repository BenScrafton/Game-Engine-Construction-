#include "Paralax.h"

void Paralax::Process()
{
	//move the gameObject back in the oposite direction a by a percentage of the actual move
	m_gameObject->pos.x -= (m_gameObject->GetParent()->GetMove().x * paralaxFactor);
	m_gameObject->pos.y -= (m_gameObject->GetParent()->GetMove().y * paralaxFactor);
	
}
